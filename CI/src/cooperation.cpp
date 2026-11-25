#include "../include/cooperation.hpp"

// Порядок аргументов: имя проекта, версия, папка с архивами, основная папка

Project::Project(std::string pname, std::string pversion, std::string pdir_path, std::string pmainPath) : 
    name(pname), 
    version(pversion)
{
dir_path = pdir_path;
mainPath = pmainPath;
}
std::filesystem::path Project::getfolder() {
    std::filesystem::path path{dir_path};
    return path;
}
void Project::ignore(std::string path){
    ignorelist.push_back(path);
}
void Project::scan() 
{
m_Scan(mainPath);
}

bool Project::save()
{
return m_Save(name, version, dir_path, mainPath, ignorelist);
}
bool Project::savem() 
{
return m_Save(name, version, dir_path, mainPath, ignorelist, commit); 
}

bool Project::load()
{
return m_Load(name, version, mainPath, dir_path);
}
bool Project::loadf(){
    return m_Load(name, version, mainPath, dir_path, file);
}

void Project::cd(std::string pdir_path, std::string pmainPath) {
dir_path = pdir_path;
mainPath = pmainPath;
}

void Project::change(std::string namep, std::string versionp) {
name = namep;
version = versionp;
}
void Project::change(std::string namep, std::string versionp, std::string filep) {
name = namep;
version = versionp;
file = filep;
}
void Project::changec(std::string namep, std::string versionp, std::string commitp) {
name = namep;
version = versionp;
commit = commitp;
}
bool Project::_delete() {
std::string zipname = name + "@" + version + ".zip";
std::filesystem::path full = std::filesystem::path(dir_path) / zipname;
return std::filesystem::remove(full);
}