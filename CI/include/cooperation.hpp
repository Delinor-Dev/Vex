#include "../../core/include/loader.hpp"
#include "../../core/include/saver.hpp"
#include "../../core/include/scanner.hpp"

// Порядок аргументов: имя проекта, версия, папка с архивами, основная папка

class Project {
private:
std::string name;
std::string version;
static std::string dir_path;
static std::string mainPath;

public:
Project(std::string pname, std::string pversion, std::string pdir_path, std::string pmainPath);
static void scan();
void save();
void load();
static void cd(std::string, std::string);
};