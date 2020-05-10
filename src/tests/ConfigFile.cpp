//
// Created by lhumphreys on 09/05/2020.
//

#include "ConfigFile.h"
#include <fstream>

ConfigFile::ConfigFile(const std::string &fname, const std::string &content)
    : filepath(std::filesystem::absolute(fname))
{
    std::ofstream fileToWrite;
    fileToWrite.open(AbsolutePath(), std::ofstream::trunc);
    fileToWrite << content;
    fileToWrite.close();
}

ConfigFile::~ConfigFile() {
    std::filesystem::remove(filepath);
}

const char* const ConfigFile::AbsolutePath() const {
    return filepath.c_str();
}
