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
void save();
void change(std::string, std::string);
void load();
void _delete();
static void cd(std::string, std::string);

private:
std::string name;
std::string version;
inline static std::string dir_path;
inline static std::string mainPath;
};