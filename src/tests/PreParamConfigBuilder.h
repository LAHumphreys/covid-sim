//
// Created by lhumphreys on 10/05/2020.
//

#ifndef COVIDTEST_PREPARAMCONFIGBUILDER_H
#define COVIDTEST_PREPARAMCONFIGBUILDER_H

#include <memory>
#include "ConfigFile.h"

class PreParamConfigBuilder {
public:
    std::unique_ptr<ConfigFile> BuildConfig (const std::string& fname = "preParams.dat");
};


#endif //COVIDTEST_PREPARAMCONFIGBUILDER_H
