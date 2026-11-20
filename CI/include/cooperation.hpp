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
bool load();
bool loadf();
bool _delete();
static void cd(std::string, std::string);

private:
std::string name;
std::string version;
std::string file;
inline static std::string dir_path;
inline static std::string mainPath;
};