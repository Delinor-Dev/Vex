#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "miniz.h"
#include <filesystem>

//сжатие папки в zip
bool m_Save(
const    std::string& name, 
const    std::string& version,
const    std::string& inpath,
const    std::string& outpath);