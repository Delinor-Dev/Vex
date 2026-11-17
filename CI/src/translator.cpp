#include "../include/translator.hpp"

Parser::Parser(std::string p_path) : VexPath(p_path)
{
valid["project"] = 2;
valid["ignore"] = 1;
valid["save"] = 2;
valid["open"] = 2;
valid["load"] = 3;
valid["delete"] = 2;
valid["list"] = 0;
current = nullptr;

}
Parser::~Parser(){
    delete current;
}

int Parser::getTokens(std::string line) 
{
    command.clear();
    if (line.find('(') == std::string::npos || line.find(')') == std::string::npos) {
        return 1;
    } 

    std::string buffer;
    int c{0};
    for (auto elem : line){
        if (elem == '(') {
            command.push_back(buffer);
            buffer.clear();
        } else if (elem == ')') {break;}
        else if (elem == '"' && c == 1) {
            command.push_back(buffer);
            buffer.clear();
            c = 0;
        }
        else if (elem == '"' && c != 1) {
            c++; //отсылочка)
            buffer.clear();
        }

        else {
            buffer += elem;
        }

    }
    return 0;
}

bool Parser::isValid() 
{
if (command.empty()) return false;
auto ic = valid.find(command[0]);
if (ic == valid.end()) {
    return false;
}
if (command.size()-1 != valid[command[0]]) {
    return false;
}
return true;

}

bool Parser::translate() 
{
    std::ifstream file(VexPath);
    if (!file.is_open()) return false;
    std::string line;
    while (std::getline(file, line)) {
        getTokens(line);
        if (isValid()){
            _do();
        }
    }
    file.close();
    return true;
}
void Parser::_do() 
{
std::string current_command = command[0];

if (current_command == "project") {
delete current;
current = new Project("", "", command[1], command[2]);
}
else if (current_command == "save") {
current->change(command[1], command[2]);
current->save();
}
else if (current_command == "open") {
current->change(command[1], command[2]);
current->load();
}
else if (current_command == "delete") {
current->change(command[1], command[2]);
current->_delete();
}
else if (current_command == "list") {
current->scan();
}
}

int main(){
    Parser p("/work_ssd/Проекты 10.10.2026-х.х.х/Vex/info.vex");
    p.translate();
}