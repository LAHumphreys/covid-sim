//
// Created by lhumphreys on 09/05/2020.
//

#ifndef COVIDTEST_CONFIGFILE_H
#define COVIDTEST_CONFIGFILE_H
#include <string>
#include <filesystem>

class ConfigFile {
public:
    ConfigFile(const std::string& fname, const std::string& content);
    virtual ~ConfigFile();

    const char* const AbsolutePath() const;

private:
    std::filesystem::path filepath;

};


#endif //COVIDTEST_CONFIGFILE_H
