#pragma once

#include "cooperation.hpp"
#include <fstream>
#include <unordered_map>

class Parser {
friend int main();
public:
Parser(std::string p_path);
bool translate();

private:
std::string VexPath;
std::vector<std::string> command;
std::unordered_map<std::string, int> valid;
int getTokens(std::string line);
bool isValid();
void _do();
};