//
// Created by lhumphreys on 10/05/2020.
//

#ifndef COVIDTEST_PREPARAMCONFIGBUILDER_H
#define COVIDTEST_PREPARAMCONFIGBUILDER_H

#include <memory>
#include <optional>
#include "ConfigFile.h"

struct PreParamConfigBuilder {
    std::unique_ptr<ConfigFile> BuildConfig (const std::string& fname = "preParams.dat");

    std::optional<std::string> updateTimestep = "0.25";
    std::optional<std::string> samplingTimestep = "1";
    std::optional<std::string> samplingTotalTime = "720";

    std::optional<std::string> numberOfRealisations = "1";
    std::optional<std::string> numberOfNonExtinctRealisations = "1";
    std::optional<std::string> onlyOutputNonExtinctRealisations = "0";

    std::optional<std::string> maxNumForSmallOutbreak = "10000";

    std::optional<std::string> numMicroCellsPerSpatialCell = "9";


    std::optional<std::string> outputAge;
    std::optional<std::string> outputSeverityAdminUnit;
    std::optional<std::string> outputR0;
    std::optional<std::string> outputControls;
    std::optional<std::string> outputCountry;
    std::optional<std::string> outputAdUnitVar;
    std::optional<std::string> outputHousehold;
    std::optional<std::string> outputInfType;
    std::optional<std::string> outputNonSeverity;
    std::optional<std::string> outputNonSummaryResults;

    std::optional<std::string> householdAttackRate = "0.1";
    std::optional<std::string> householdTransPowerDenom = "0.8"; // see Cauchemez 2004. Deals with impact of increasing size of households on transmitablility

    std::optional<std::string> includeAdUnitsWithinCountries = "1.0";
    std::optional<std::string> outputAdunitIncidence = "0";
};


#endif //COVIDTEST_PREPARAMCONFIGBUILDER_H
