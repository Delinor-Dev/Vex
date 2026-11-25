#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "miniz.h"
#include <filesystem>
#include <fstream>
#include <algorithm>

//сжатие папки в zip
bool m_Save(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath,
const    std::string& outpath,
const    std::vector<std::string>& ignorelist);
bool m_Save(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath,
const    std::string& outpath,
const    std::vector<std::string>& ignorelist,
const    std::string& commit);
