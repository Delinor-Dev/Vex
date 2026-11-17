#include "../include/cooperation.hpp"

// Порядок аргументов: имя проекта, версия, папка с архивами, основная папка

Project::Project(std::string pname, std::string pversion, std::string pdir_path, std::string pmainPath) : 
    name(pname), 
    version(pversion)
{
dir_path = pdir_path;
mainPath = pmainPath;
}

void Project::scan() 
{
m_Scan(dir_path);
}

void Project::save()
{
m_Save(name, version, dir_path, mainPath);
}

void Project::load()
{
m_Load(name, version, mainPath, dir_path);
}

void Project::cd(std::string pdir_path, std::string pmainPath) {
dir_path = pdir_path;
mainPath = pmainPath;
}

void Project::change(std::string namep, std::string versionp) {
name = namep;
version = versionp;
}

void Project::_delete() {
std::string zipname = name + "@" + version + ".zip";
std::filesystem::path full = std::filesystem::path(dir_path) / zipname;
std::filesystem::remove(full);
}