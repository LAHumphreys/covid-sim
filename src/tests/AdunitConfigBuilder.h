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

    std::optional<std::string> kernelType = "2";
    std::optional<std::string> kernelScale = "4000";
    std::optional<std::string> kernelShape = "3";
    std::optional<std::string> kernelResolution = "2000000";
    std::optional<std::string> kernelHigherResolutionFactor = "40";
    std::optional<std::string> kernelParam3;
    std::optional<std::string> kernelParam4;
    std::optional<std::string> kernelShapeParamForPlaces = "3 3 3 3";
    std::optional<std::string> kernelScaleParamForPlaces = "4000 4000 4000 4000";
    std::optional<std::string> kernelTypeForPlaces;
    std::optional<std::string> kernelParam3ForPlaces;
    std::optional<std::string> kernelParam4ForPlaces;

    std::optional<std::string> doHouseholds;
    std::optional<std::string> householdSizeDist = "0.305305	0.342342	0.159159	0.136136	0.040040	0.011243	0.003677	0.001256	0.000453	0.000388";
    std::optional<std::string> correctHouseAgeDistToExactGeography = "1";

    std::optional<std::string> divisorForCountries = "100000";


    std::unique_ptr<ConfigFile> BuildCfgFile(const std::string& fname = "admin.txt") const;
};


#endif //COVIDTEST_ADUNITCONFIGBUILDER_H
