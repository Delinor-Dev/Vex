#include "../include/translator.hpp"

Parser::Parser(std::string p_path) : VexPath(p_path)
{
valid["project"] = 1;
valid["ignore"] = 1;
valid["save"] = 2;
valid["open"] = 2;
valid["load"] = 3;
valid["delete"] = 2;
valid["list"] = 0;
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
            std::cout << command[0] << std::endl;
            _do();
        }
    }
    file.close();
    return true;
}
void Parser::_do() {
    std::cout << "OK!" << std::endl;
}

int main(){
    Parser p("/work_ssd/Проекты 10.10.2026-х.х.х/Vex/info.vex");
    p.translate();
}