#include "../include/scanner.hpp"

void m_Scan(std::string inpath) {
    for (const auto& entry : std::filesystem::directory_iterator(inpath)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().stem().string();
            std::string buffer;
            bool isp = false;
            for (char ch : filename) {
                if (ch != '@') {
                    buffer += ch;
                }
                else {
                    std::cout << "Project: " << buffer << "    ";
                    buffer = "";
                    isp = true;
                }
            }
            if (isp){
            std::cout << "Version: " << buffer << std::endl;}
        }
    }
}

std::string m_Find(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath) 
{
    std::string target = name + "@" + version + ".zip";
    if (std::filesystem::exists(std::filesystem::path(inpath) / target)) {
        return target;
    }
    return "0";
}