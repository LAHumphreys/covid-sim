//
// Created by lhumphreys on 10/05/2020.
//

#ifndef COVIDTEST_PARAMSCONFIGBUILDER_H
#define COVIDTEST_PARAMSCONFIGBUILDER_H

#include <memory>
#include "ConfigFile.h"


class ParamsConfigBuilder {
public:
    std::unique_ptr<ConfigFile> BuildConfig (const std::string& fname = "preParams.dat");

};


#endif //COVIDTEST_PARAMSCONFIGBUILDER_H
