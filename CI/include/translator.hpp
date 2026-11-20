#pragma once

#include "cooperation.hpp"
#include <fstream>
#include <unordered_map>
#include <memory>

class Parser {
public:
Parser(std::string p_path);
std::unique_ptr<Project> current;
bool translate();

private:
std::string VexPath;
std::vector<std::string> command;
std::unordered_map<std::string, int> valid;
int getTokens(std::string line);
bool isValid();
bool _do(int, std::string&);
bool pr{false};
};