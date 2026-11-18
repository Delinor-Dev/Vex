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
    std::cout << "Welcome to Vex!\n";
    std::ifstream file(VexPath);
    if (!file.is_open()) {std::cout << "Error opening file! Make sure that info.vex is in the current working directory.\n"; return false;}
    std::string line;
    int counter{0};
    while (std::getline(file, line)) {
        counter++;
        getTokens(line);
        if (isValid()){

            if (!_do(counter)) {
                file.close();
                return false;
            }
        }
        else if (!isValid() && !command.empty()) {file.close(); std::cout << "Line " << counter << ":\nError reading line \"" << line << "\".\nPlease check syntax rules at https://github.com/Delinor-Dev/Vex/blob/main/README.md#infovex\n"; return false;}
    }
    file.close();
    return true;
}

bool Parser::_do(int counter)
{
std::string current_command = command[0];

if (current_command == "project") {
pr = true;
current = std::make_unique<Project>("", "", command[1], command[2]);
}
else if (current_command == "save" && pr) {
current->change(command[1], command[2]);
current->save();
}
else if (current_command == "open" && pr) {
current->change(command[1], command[2]);
current->load();
}
else if (current_command == "delete" && pr) {
current->change(command[1], command[2]);
current->_delete();
}
else if (current_command == "list" && pr) {
current->scan();
}
else {
    std::cout << "Line: " << counter << "\nError! Run 'project' command first.\nMore info at https://github.com/Delinor-Dev/Vex/blob/main/README.md#infovex"; 
    exit(1);
}
return true;
}
