#include "../include/saver.hpp"

bool m_Save(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath,
const    std::string& outpath)
{
    std::string zipname = name + "@" + version + ".zip";
    std::filesystem::path full = std::filesystem::path(outpath) / zipname;
    std::filesystem::remove(full);
    std::vector<std::pair<std::string, std::string>> files;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(inpath)) {
        if (entry.is_regular_file()) {
            files.push_back({
                std::filesystem::relative(entry.path(), inpath).generic_string(),
                entry.path().string()
            });
        }
    }

    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));
    if (!mz_zip_writer_init_file(&zip, full.string().c_str(), 0)) {
        mz_zip_error err = mz_zip_get_last_error(&zip);
        return 0;
    }

    for (const auto& path : files) {
        mz_bool ok = mz_zip_writer_add_file(&zip, path.first.c_str(), path.second.c_str(), NULL, 0, MZ_DEFAULT_LEVEL);
        if (!ok) {
            mz_zip_writer_end(&zip);
            return false;
        }
    }

    mz_zip_writer_finalize_archive(&zip);
    mz_zip_writer_end(&zip);
    return true;
}
bool m_Save(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath,
const    std::string& outpath,
const    std::string& commit) {
    std::string zipname = name + "@" + version + ".zip";
    std::filesystem::path full = std::filesystem::path(outpath) / zipname;
    std::filesystem::remove(full);
    std::vector<std::pair<std::string, std::string>> files;
    std::filesystem::path meta = std::filesystem::path(inpath) / "metaVex.txt";
    std::ofstream outFile(meta);
    outFile << commit;
    outFile.close();
    for (const auto& entry : std::filesystem::recursive_directory_iterator(inpath)) {
        if (entry.is_regular_file()) {
            files.push_back({
                std::filesystem::relative(entry.path(), inpath).generic_string(),
                entry.path().string()
            });
        }
    }

    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));
    if (!mz_zip_writer_init_file(&zip, full.string().c_str(), 0)) {
        mz_zip_error err = mz_zip_get_last_error(&zip);
        return 0;
    }

    for (const auto& path : files) {
        mz_bool ok = mz_zip_writer_add_file(&zip, path.first.c_str(), path.second.c_str(), NULL, 0, MZ_DEFAULT_LEVEL);
        if (!ok) {
            mz_zip_writer_end(&zip);
            return false;
        }
    }
    std::filesystem::remove(meta);
    mz_zip_writer_finalize_archive(&zip);
    mz_zip_writer_end(&zip);
    return true;
}