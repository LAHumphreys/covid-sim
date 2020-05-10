//
// Created by lhumphreys on 10/05/2020.
//

#ifndef COVIDTEST_ADUNITCONFIGBUILDER_H
#define COVIDTEST_ADUNITCONFIGBUILDER_H
#include <memory>
#include <optional>
#include "ConfigFile.h"


struct AdunitConfigBuilder {
    std::optional<std::string> populationSize = "66777534";
    std::optional<std::string> doHouseholds;
    std::unique_ptr<ConfigFile> BuildCfgFile(const std::string& fname = "admin.txt") const;
};


#endif //COVIDTEST_ADUNITCONFIGBUILDER_H
