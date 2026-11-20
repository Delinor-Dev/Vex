#include "../include/scanner.hpp"
#include "../include/loader.hpp"
#include "../include/saver.hpp"

bool m_Load(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath,
const    std::string& outpath) 
{
    std::string file = m_Find(name, version, inpath);
    if (file == "0") return false;
    mz_zip_archive zip{};
    std::filesystem::path full = std::filesystem::path(inpath) / file;
    if (!mz_zip_reader_init_file(&zip, full.string().c_str(), 0)) {
        return false;
    }
    mz_uint count = mz_zip_reader_get_num_files(&zip);
    for (mz_uint i = 0; i < count; i++){
        mz_zip_archive_file_stat stat;
        if (!mz_zip_reader_file_stat(&zip, i, &stat)) continue;
        std::filesystem::path dest = std::filesystem::path(outpath) / stat.m_filename;

        if (mz_zip_reader_is_file_a_directory(&zip, i)) {
            std::filesystem::create_directories(dest);

        } else {
            std::filesystem::create_directories(dest.parent_path());
            if (!mz_zip_reader_extract_to_file(&zip, i, dest.string().c_str(), 0)) {
                mz_zip_reader_end(&zip);
                return false;
            }
        }
    }
    mz_zip_reader_end(&zip);
    return true;
}

bool m_Load(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath,
const    std::string& outpath,
const    std::string& filename
) 
{

    std::string file = m_Find(name, version, inpath);
    if (file == "0") return false;
    mz_zip_archive zip{};
    std::filesystem::path full = std::filesystem::path(inpath) / file;
    if (!mz_zip_reader_init_file(&zip, full.string().c_str(), 0)) {
        return false;
    }

    std::filesystem::path target = std::filesystem::path(filename).relative_path();
    if (!target.has_filename()){
        target = target.parent_path();
    }
    bool extr = false;
    mz_uint count = mz_zip_reader_get_num_files(&zip);
    for (mz_uint i = 0; i < count; i++){
        mz_zip_archive_file_stat stat;
        if (!mz_zip_reader_file_stat(&zip, i, &stat)) continue;
        std::filesystem::path enp(stat.m_filename);
        bool isdir = mz_zip_reader_is_file_a_directory(&zip, i);
        std::filesystem::path clean = isdir ? enp.parent_path() : enp;
        std::cout << clean << "\n";
        if (clean == target){
            
        std::filesystem::path dest = std::filesystem::path(outpath) / target.filename();
        if (isdir) {
            std::filesystem::create_directories(dest);
        } else {
            std::filesystem::create_directories(dest.parent_path());
            if (!mz_zip_reader_extract_to_file(&zip, i, dest.string().c_str(), 0)){
                mz_zip_reader_end(&zip);
                return false;
            }
        }
        extr = true;

        }
        else if (clean.string().rfind(target.string() + "/", 0) == 0) {

        std::filesystem::path rel = std::filesystem::relative(clean, target);
        std::filesystem::path dest = std::filesystem::path(outpath) / target.filename() / rel;
        if (isdir) {
            std::filesystem::create_directories(dest);
        } else {
            std::filesystem::create_directories(dest.parent_path());
            if (!mz_zip_reader_extract_to_file(&zip, i, dest.string().c_str(), 0)){
                mz_zip_reader_end(&zip);
                return false;
            }
        }
        extr = true;
        }
        mz_zip_reader_end(&zip);
    }

    return extr;
}