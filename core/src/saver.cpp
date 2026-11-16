#include "../include/saver.hpp"

bool m_Save(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath,
const    std::string& outpath)
{
    //добавляем все файлы в строковый массив путей
    std::string zipname = name + "_" + version + ".zip";
    std::vector<std::string> files;
    
    for (const auto& entry : std::filesystem::recursive_directory_iterator(inpath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().generic_string());
        }
    }
    //инициализируем архив и записываем туда все что нужно
    mz_zip_archive zip;
    memset(&zip, 0, sizeof(zip));
    if (!mz_zip_writer_init_file(&zip, (outpath + zipname).c_str(), 0)) {
        return false;
    }
    for (const auto& path : files){
        mz_bool ok = mz_zip_writer_add_file(&zip, path.c_str(), path.c_str(), NULL, 0, MZ_DEFAULT_LEVEL);
        if (!ok){
            mz_zip_writer_end(&zip);
            return false;
        }
    }
    mz_zip_writer_finalize_archive(&zip);
    mz_zip_writer_end(&zip);

    return true;
}
