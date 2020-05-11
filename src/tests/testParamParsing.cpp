#include <gtest/gtest.h>
#include "CovidSimTestFixture.h"
#include "CovidSimCmdLineArgs.h"
#include "PreParamConfigBuilder.h"
#include "AdunitConfigBuilder.h"
#include "ParamsConfigBuilder.h"
#include <cmath>

class ParamParsingTest: public CovidSimTestFixture {
protected:
    CovidSimCmdLineArgs args;
    PreParamConfigBuilder preParams;
    ParamsConfigBuilder params;
    AdunitConfigBuilder adUnit;

    void SetUp() override {
        CovidSimTestFixture::SetUp();
        args.paramFile = "params.txt";
        args.preParamFile = "preParams.txt";
        args.adminFile = "admin.txt";
        args.r0 = "1.5";
        args.maxThreads = "1";
    }

    void SetupAndParseParams() {
        InvokeParseCmdLine(args.BuildCmdLine());
        InvokeSetupThreads();
        auto paramFile = params.BuildConfig(ParamFile);
        auto preParamFile = preParams.BuildConfig(PreParamFile);
        auto adUnitFile = adUnit.BuildCfgFile(AdunitFile());

        InvokeReadParams();
    }
};

TEST_F(ParamParsingTest, DefaultValues) {
    SetupAndParseParams();
}

namespace {
    class TimeStep: public ParamParsingTest{};
    class Population: public ParamParsingTest {};
    class Realisations: public ParamParsingTest {};
    class SmallEpidemic: public ParamParsingTest {};
    class Cells: public ParamParsingTest {};
    class Households: public ParamParsingTest {};
    class Output: public ParamParsingTest {};
    class Kernel: public ParamParsingTest {};
    class AdUnits: public ParamParsingTest {};
}

TEST_F(AdUnits, Specified) {
    preParams.includeAdUnitsWithinCountries = "1";
    adUnit.divisorForCountries = "1000";
    preParams.outputAdunitIncidence = "1";
    SetupAndParseParams();
    ASSERT_EQ(P().DoAdUnits, 1);
    ASSERT_EQ(P().CountryDivisor, 1000);
    ASSERT_EQ(P().DoAdunitOutput, 1);
}
TEST_F(AdUnits, Disabled) {
    preParams.includeAdUnitsWithinCountries = "0";
    SetupAndParseParams();
    ASSERT_EQ(P().DoAdUnits, 0);
    ASSERT_EQ(P().DoAdunitBoundaries, 0);
    ASSERT_EQ(P().DoAdunitBoundaryOutput, 0);
    ASSERT_EQ(P().DoAdunitOutput, 0);
    ASSERT_EQ(P().DoCorrectAdunitPop, 0);
    ASSERT_EQ(P().DoSpecifyPop, 0);
    ASSERT_EQ(P().AdunitLevel1Divisor, 1);
    ASSERT_EQ(P().AdunitLevel1Mask, 1000000000);
    ASSERT_EQ(P().AdunitBitmapDivisor, 1);
}
TEST_F(AdUnits, DefaultEnabled) {
    preParams.includeAdUnitsWithinCountries.reset();
    adUnit.divisorForCountries.reset();
    preParams.outputAdunitIncidence.reset();
    SetupAndParseParams();
    ASSERT_EQ(P().DoAdUnits, 1);
    ASSERT_EQ(P().CountryDivisor, 1);
    ASSERT_EQ(P().DoAdunitOutput, 0);
}
TEST_F(Kernel, Specified) {
    adUnit.kernelResolution = "2000000";
    adUnit.kernelHigherResolutionFactor  = "40";
    adUnit.kernelType = "2";
    adUnit.kernelScale = "4000";
    adUnit.kernelParam3 = "3";
    adUnit.kernelParam4 = "4";
    adUnit.kernelShape = "3";
    adUnit.kernelScaleParamForPlaces = "3000 3500 4000 4500";
    adUnit.kernelShapeParamForPlaces = "2 3 4 5";
    adUnit.kernelParam3ForPlaces = "1 2 3 4";
    adUnit.kernelParam4ForPlaces = "5 6 7 8";
    SetupAndParseParams();
    ASSERT_EQ(P().NKR, 2e6);
    ASSERT_EQ(P().NK_HR, 40);
    ASSERT_EQ(P().MoveKernelType, 2);
    ASSERT_EQ(P().MoveKernelShape, 3);
    ASSERT_EQ(P().MoveKernelScale, 4000);
    ASSERT_EQ(P().MoveKernelP3, 3);
    ASSERT_EQ(P().MoveKernelP4, 4);

    ASSERT_EQ(P().PlaceTypeKernelScale[0], 3000);
    ASSERT_EQ(P().PlaceTypeKernelScale[1], 3500);
    ASSERT_EQ(P().PlaceTypeKernelScale[2], 4000);
    ASSERT_EQ(P().PlaceTypeKernelScale[3], 4500);

    ASSERT_EQ(P().PlaceTypeKernelShape[0], 2);
    ASSERT_EQ(P().PlaceTypeKernelShape[1], 3);
    ASSERT_EQ(P().PlaceTypeKernelShape[2], 4);
    ASSERT_EQ(P().PlaceTypeKernelShape[3], 5);

    ASSERT_EQ(P().PlaceTypeKernelP3[0], 1);
    ASSERT_EQ(P().PlaceTypeKernelP3[1], 2);
    ASSERT_EQ(P().PlaceTypeKernelP3[2], 3);
    ASSERT_EQ(P().PlaceTypeKernelP3[3], 4);

    ASSERT_EQ(P().PlaceTypeKernelP4[0], 5);
    ASSERT_EQ(P().PlaceTypeKernelP4[1], 6);
    ASSERT_EQ(P().PlaceTypeKernelP4[2], 7);
    ASSERT_EQ(P().PlaceTypeKernelP4[3], 8);
}
TEST_F(Kernel, CmdLineScales) {
    args.kernelOffsetScale = "1.5";
    args.kernelPowerScale = "2.5";

    adUnit.kernelResolution = "2000000";
    adUnit.kernelHigherResolutionFactor  = "40";
    adUnit.kernelType = "3";
    adUnit.kernelScale = "4000";
    adUnit.kernelShape = "3";
    adUnit.kernelParam3 = "3";
    adUnit.kernelParam4 = "4";
    adUnit.kernelScaleParamForPlaces.reset();
    adUnit.kernelShapeParamForPlaces.reset();
    adUnit.kernelParam3ForPlaces.reset();
    adUnit.kernelParam4ForPlaces.reset();
    SetupAndParseParams();
    ASSERT_EQ(P().NKR, 2e6);
    ASSERT_EQ(P().NK_HR, 40);
    ASSERT_EQ(P().MoveKernelType, 3);
    ASSERT_EQ(P().MoveKernelScale, 4000 * 1.5);
    ASSERT_EQ(P().MoveKernelP3, 3);
    ASSERT_EQ(P().MoveKernelP4, 4);
    ASSERT_EQ(P().MoveKernelShape, 3 * 2.5);

    ASSERT_EQ(P().PlaceTypeKernelScale[0], 4000 *1.5);
    ASSERT_EQ(P().PlaceTypeKernelScale[1], 4000 *1.5);
    ASSERT_EQ(P().PlaceTypeKernelScale[2], 4000 *1.5);
    ASSERT_EQ(P().PlaceTypeKernelScale[3], 4000 *1.5);

    ASSERT_EQ(P().PlaceTypeKernelShape[0], 3 * 2.5);
    ASSERT_EQ(P().PlaceTypeKernelShape[1], 3 * 2.5);
    ASSERT_EQ(P().PlaceTypeKernelShape[2], 3 * 2.5);
    ASSERT_EQ(P().PlaceTypeKernelShape[3], 3 * 2.5);
}
TEST_F(Kernel, CmdLineScalesNoScaleExplicitPlaceConfig) {
    args.kernelOffsetScale = "1.5";
    args.kernelPowerScale = "2.5";

    adUnit.kernelResolution = "2000000";
    adUnit.kernelHigherResolutionFactor  = "40";
    adUnit.kernelType = "3";
    adUnit.kernelScale = "4000";
    adUnit.kernelShape = "3";
    adUnit.kernelParam3 = "3";
    adUnit.kernelParam4 = "4";
    adUnit.kernelScaleParamForPlaces = "4000 4000 4000 4000";
    adUnit.kernelShapeParamForPlaces = "3 3 3 3";
    adUnit.kernelTypeForPlaces = "1 2 3 4";
    SetupAndParseParams();
    ASSERT_EQ(P().NKR, 2e6);
    ASSERT_EQ(P().NK_HR, 40);
    ASSERT_EQ(P().MoveKernelType, 3);
    ASSERT_EQ(P().MoveKernelScale, 4000 * 1.5);
    ASSERT_EQ(P().MoveKernelP3, 3);
    ASSERT_EQ(P().MoveKernelP4, 4);
    ASSERT_EQ(P().MoveKernelShape, 3 * 2.5);

    ASSERT_EQ(P().PlaceTypeKernelScale[0], 4000);
    ASSERT_EQ(P().PlaceTypeKernelScale[1], 4000);
    ASSERT_EQ(P().PlaceTypeKernelScale[2], 4000);
    ASSERT_EQ(P().PlaceTypeKernelScale[3], 4000);

    ASSERT_EQ(P().PlaceTypeKernelShape[0], 3);
    ASSERT_EQ(P().PlaceTypeKernelShape[1], 3);
    ASSERT_EQ(P().PlaceTypeKernelShape[2], 3);
    ASSERT_EQ(P().PlaceTypeKernelShape[3], 3);

    ASSERT_EQ(P().PlaceTypeKernelType[0], 1);
    ASSERT_EQ(P().PlaceTypeKernelType[1], 2);
    ASSERT_EQ(P().PlaceTypeKernelType[2], 3);
    ASSERT_EQ(P().PlaceTypeKernelType[3], 4);
}
TEST_F(Kernel, Defaulted) {
    adUnit.kernelResolution.reset();
    adUnit.kernelHigherResolutionFactor.reset();
    adUnit.kernelShape.reset();
    adUnit.kernelParam3.reset();
    adUnit.kernelParam4.reset();
    adUnit.kernelScaleParamForPlaces.reset();
    adUnit.kernelShapeParamForPlaces.reset();
    adUnit.kernelTypeForPlaces.reset();

    adUnit.kernelScale = "3500";
    adUnit.kernelType = "3";

    SetupAndParseParams();

    ASSERT_EQ(P().MoveKernelScale, 3500);

    ASSERT_EQ(P().NKR, 4e6);
    ASSERT_EQ(P().NK_HR, (4e6 / 1600));
    ASSERT_EQ(P().MoveKernelShape, 1.0);
    ASSERT_EQ(P().MoveKernelP3, 0);
    ASSERT_EQ(P().MoveKernelP4, 0);

    ASSERT_EQ(P().PlaceTypeKernelScale[0], 3500);
    ASSERT_EQ(P().PlaceTypeKernelScale[1], 3500);
    ASSERT_EQ(P().PlaceTypeKernelScale[2], 3500);
    ASSERT_EQ(P().PlaceTypeKernelScale[3], 3500);

    ASSERT_EQ(P().PlaceTypeKernelShape[0], 1.0);
    ASSERT_EQ(P().PlaceTypeKernelShape[1], 1.0);
    ASSERT_EQ(P().PlaceTypeKernelShape[2], 1.0);
    ASSERT_EQ(P().PlaceTypeKernelShape[3], 1.0);

    ASSERT_EQ(P().PlaceTypeKernelP3[0], 0);
    ASSERT_EQ(P().PlaceTypeKernelP3[1], 0);
    ASSERT_EQ(P().PlaceTypeKernelP3[2], 0);
    ASSERT_EQ(P().PlaceTypeKernelP3[3], 0);

    ASSERT_EQ(P().PlaceTypeKernelP4[0], 0);
    ASSERT_EQ(P().PlaceTypeKernelP4[1], 0);
    ASSERT_EQ(P().PlaceTypeKernelP4[2], 0);
    ASSERT_EQ(P().PlaceTypeKernelP4[3], 0);

    ASSERT_EQ(P().PlaceTypeKernelType[0], 3);
    ASSERT_EQ(P().PlaceTypeKernelType[1], 3);
    ASSERT_EQ(P().PlaceTypeKernelType[2], 3);
    ASSERT_EQ(P().PlaceTypeKernelType[3], 3);
}
TEST_F(Kernel, MandatoryKernelType) {
    adUnit.kernelType.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*`Kernel type");
}
TEST_F(Kernel, MandatoryKernelScale){
    adUnit.kernelScale.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*`Kernel scale");
}
TEST_F(Kernel, MinKernelRes) {
    adUnit.kernelResolution = "1999999";
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "[Kernel resolution] .* at least 2000000")
}
TEST_F(Kernel, KernalHigherFactorResMin) {
    adUnit.kernelHigherResolutionFactor = "0";
    adUnit.kernelResolution = "2000000";
    EXPECT_CRIT_ERROR(SetupAndParseParams(), R"REGEX(\[Kernel higher resolution factor\] needs to be in range)REGEX");
}
TEST_F(Kernel, KernalHigherFactorResMax) {
    adUnit.kernelHigherResolutionFactor = "2000000";
    adUnit.kernelResolution = "2000000";
    EXPECT_CRIT_ERROR(SetupAndParseParams(), R"REGEX(\[Kernel higher resolution factor\] needs to be in range)REGEX");
}

TEST_F(Output, Specified) {
    preParams.outputAge = "1";
    preParams.outputSeverityAdminUnit = "1";
    preParams.outputR0 = "1";
    preParams.outputControls = "1";
    preParams.outputCountry = "1";
    preParams.outputAdUnitVar = "1";
    preParams.outputHousehold = "1";
    preParams.outputInfType = "1";
    preParams.outputNonSeverity = "1";
    preParams.outputNonSummaryResults = "1";
    SetupAndParseParams();
    ASSERT_EQ(P().OutputAge, 1);
    ASSERT_EQ(P().OutputSeverityAdminUnit, 1);
    ASSERT_EQ(P().OutputR0, 1);
    ASSERT_EQ(P().OutputControls, 1);
    ASSERT_EQ(P().OutputCountry, 1);
    ASSERT_EQ(P().OutputAdUnitVar, 1);
    ASSERT_EQ(P().OutputHousehold, 1);
    ASSERT_EQ(P().OutputInfType, 1);
    ASSERT_EQ(P().OutputNonSeverity, 1);
    ASSERT_EQ(P().OutputNonSummaryResults, 1);
}
TEST_F(Output, Defaulted) {
    preParams.outputAge.reset();
    preParams.outputSeverityAdminUnit.reset();
    preParams.outputR0.reset();
    preParams.outputControls.reset();
    preParams.outputCountry.reset();
    preParams.outputAdUnitVar.reset();
    preParams.outputHousehold.reset();
    preParams.outputInfType.reset();
    preParams.outputNonSeverity.reset();
    preParams.outputNonSummaryResults.reset();
    SetupAndParseParams();
    ASSERT_EQ(P().OutputAge, 1);
    ASSERT_EQ(P().OutputSeverityAdminUnit, 1);
    ASSERT_EQ(P().OutputR0, 0);
    ASSERT_EQ(P().OutputControls, 0);
    ASSERT_EQ(P().OutputCountry, 0);
    ASSERT_EQ(P().OutputAdUnitVar, 0);
    ASSERT_EQ(P().OutputHousehold, 0);
    ASSERT_EQ(P().OutputInfType, 0);
    ASSERT_EQ(P().OutputNonSeverity, 0);
    ASSERT_EQ(P().OutputNonSummaryResults, 0);
}

TEST_F(Households, Specified) {
    adUnit.doHouseholds = "1";
    adUnit.householdSizeDist = "0.1";
    adUnit.correctHouseAgeDistToExactGeography = "1";
    preParams.householdAttackRate = "0.2";
    preParams.householdTransPowerDenom = "0.8";
    for (size_t i = 1; i < MAX_HOUSEHOLD_SIZE; ++i ) {
        adUnit.householdSizeDist.value() += "\t0.1";
    }

    SetupAndParseParams();

    ASSERT_EQ(P().DoHouseholds, 1);
    ASSERT_EQ(P().HouseholdTrans, 0.2);
    ASSERT_EQ(P().HouseholdTransPow, 0.8);
    ASSERT_TRUE(adUnit.correctHouseAgeDistToExactGeography);
    double cummulativeDist = 0.0;
    for (size_t i = 0; i < MAX_HOUSEHOLD_SIZE; ++i ) {
        const size_t householdSize = i+1;
        cummulativeDist += 0.1;
        // stored distrib is cummlative
        ASSERT_FLOAT_EQ(P().HouseholdSizeDistrib[0][i], cummulativeDist) << "Failed on item: " << i;
        ASSERT_FLOAT_EQ(P().HouseholdDenomLookup[i], 1.0 / std::pow((double)householdSize, 0.8));
    }
}
TEST_F(Households, Disabled) {
    adUnit.doHouseholds = "0";
    SetupAndParseParams();
    ASSERT_EQ(P().DoHouseholds, 0);
    ASSERT_EQ(P().HouseholdTrans, 0.0);
    ASSERT_EQ(P().HouseholdTransPow, 1.0);
    ASSERT_EQ(P().HouseholdSizeDistrib[0][0], 1.0);
    for (size_t i = 1; i < MAX_HOUSEHOLD_SIZE; ++i ) {
        ASSERT_EQ(P().HouseholdSizeDistrib[i][0], 0.0);
    }
}
TEST_F(Households, MandatoryHouseAttackRates) {
    adUnit.doHouseholds = "1";
    preParams.householdAttackRate.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*`Household attack rate'");
}
TEST_F(Households, MandatoryHouseTransPower) {
    adUnit.doHouseholds = "1";
    preParams.householdTransPowerDenom.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*`Household transmission denominator power'");
}
TEST_F(Households, MandatorySizeDist) {
    adUnit.doHouseholds = "1";
    adUnit.householdSizeDist.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*`Household size distribution'");
}
TEST_F(Households, DefaultEnabled) {
    adUnit.doHouseholds.reset();
    adUnit.correctHouseAgeDistToExactGeography.reset();
    SetupAndParseParams();
    ASSERT_EQ(P().DoHouseholds, 1);
    ASSERT_EQ(P().DoCorrectAgeDist, 0);
}
TEST_F(Cells, NumMicroCellsMandatory) {
    preParams.numMicroCellsPerSpatialCell.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*`Number of micro-cells");
}
TEST_F(Cells, Specified) {
    preParams.numMicroCellsPerSpatialCell = "9";
    SetupAndParseParams();
    ASSERT_EQ(P().NMCL, 9);
}
TEST_F(SmallEpidemic, Specified) {
    preParams.maxNumForSmallOutbreak = "1000";
    SetupAndParseParams();
    ASSERT_EQ(P().SmallEpidemicCases, 1000);
}
TEST_F(SmallEpidemic, Defaulted) {
    preParams.maxNumForSmallOutbreak.reset();
    SetupAndParseParams();
    ASSERT_EQ(P().SmallEpidemicCases, -1);
}

TEST_F(TimeStep, ReadSteps) {
    preParams.updateTimestep = "0.25";
    preParams.samplingTimestep = "1.5";
    preParams.samplingTotalTime = "700";
    SetupAndParseParams();
    ASSERT_EQ(P().TimeStep, 0.25);
    ASSERT_EQ(P().SampleStep, 1.5);
    ASSERT_EQ(P().UpdatesPerSample, 6);
    ASSERT_EQ(P().TimeStepsPerDay, 4);
    ASSERT_EQ(P().SampleTime, 700);
    ASSERT_EQ(P().NumSamples, 467 + 1);
}
TEST_F(TimeStep, SampleStepCanNotBeSmallerThanUpdateStep) {
    preParams.updateTimestep = "0.25";
    preParams.samplingTimestep = "0.125";
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Update step.*smaller.*sampling step");
}
TEST_F(TimeStep, MandatoryUpdateTimestep) {
    preParams.updateTimestep.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*`Update timestep'");
}
TEST_F(TimeStep, MandatorySampleStep) {
    preParams.samplingTimestep.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*`Sampling timestep'");
}
TEST_F(TimeStep, MandatorySamplingTime) {
    preParams.samplingTotalTime.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*`Sampling time' ");
}

TEST_F(Realisations, Specified) {
    preParams.numberOfRealisations = "2";
    preParams.numberOfNonExtinctRealisations = "1";
    preParams.onlyOutputNonExtinctRealisations = "1";
    SetupAndParseParams();
    EXPECT_EQ(P().NumRealisations, 2);
    EXPECT_EQ(P().NumNonExtinctRealisations, 1);
    EXPECT_EQ(P().OutputOnlyNonExtinct, 1);
}
TEST_F(Realisations, Mandatory) {
    preParams.numberOfRealisations.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*`Number of realisations' ");
}
TEST_F(Realisations, DefaultValues) {
    preParams.numberOfRealisations = "2";
    preParams.numberOfNonExtinctRealisations.reset();
    preParams.onlyOutputNonExtinctRealisations.reset();
    SetupAndParseParams();
    EXPECT_EQ(P().NumRealisations, 2);
    EXPECT_EQ(P().NumNonExtinctRealisations, 2);
    EXPECT_EQ(P().OutputOnlyNonExtinct, 0);
}

TEST_F(Population, Specified) {
    adUnit.populationSize = "66000000";
    SetupAndParseParams();
    ASSERT_EQ(P().PopSize, 66000000);
}
TEST_F(Population, MandatoryParam) {
    adUnit.populationSize.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*`Population size' ");
}










