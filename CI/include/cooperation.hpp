#pragma once

#include "../../core/include/loader.hpp"
#include "../../core/include/saver.hpp"
#include "../../core/include/scanner.hpp"

// Порядок аргументов: имя проекта, версия, папка с архивами, основная папка

class Project {
friend class Parser;
public:
Project(std::string pname, std::string pversion, std::string pdir_path, std::string pmainPath);
static void scan();
bool save();
void change(std::string, std::string);
void change(std::string, std::string, std::string);
void changec(std::string, std::string, std::string);
void ignore(std::string);
bool savem();
bool load();
bool loadf();
bool _delete();
std::filesystem::path getfolder();
static void cd(std::string, std::string);

private:
std::string name;
std::string version;
std::string file;
std::string commit;
std::vector<std::string> ignorelist;
inline static std::string dir_path;
inline static std::string mainPath;
};