#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "miniz.h"
#include <filesystem>

//Перебор всех файлов
void m_Scan(std::string);
//Поиск конкретного файла
std::string m_Find(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath);