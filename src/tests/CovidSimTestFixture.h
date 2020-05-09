#ifndef COVIDTEST_COVIDSIMTESTFIXTURE_H
#define COVIDTEST_COVIDSIMTESTFIXTURE_H

#include <gtest/gtest.h>
#include "Param.h"

class CovidSimTestFixture: public ::testing::Test {
private:
    static constexpr size_t MAXINTFILE=10;
public:
    void SetUp() override;
    void InvokeReadParam(const std::vector<std::string>& args);

protected:
    param& P();
    char* OutFile() const;
    char* OutFileBase() const;
    char* OutDensFile() const;

    // variable initialised in CovidSImp.cpp:main
    char ParamFile[1024]{}, DensityFile[1024]{}, NetworkFile[1024]{}, AirTravelFile[1024]{}, SchoolFile[1024]{}, RegDemogFile[1024]{}, InterventionFile[MAXINTFILE][1024]{}, PreParamFile[1024]{}, buf[2048]{}, * sep;
    int GotPP, GotAP, GotScF, Perr;

private:
    void CovidSimMainInitialisation();

};


#endif //COVIDTEST_COVIDSIMTESTFIXTURE_H
