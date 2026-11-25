#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "miniz.h"
#include <filesystem>
#include <fstream>

//сжатие папки в zip
bool m_Save(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath,
const    std::string& outpath);
bool m_Save(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath,
const    std::string& outpath,
const    std::string& commit);