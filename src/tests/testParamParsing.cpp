#include <gtest/gtest.h>
#include "CovidSimTestFixture.h"
#include "CovidSimCmdLineArgs.h"
#include "PreParamConfigBuilder.h"
#include "AdunitConfigBuilder.h"
#include "ParamsConfigBuilder.h"

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
    adUnit.doHouseholds = "0";
    SetupAndParseParams();
    ASSERT_EQ(P().DoHouseholds, 0);
}
TEST_F(Households, Defaulted) {
    adUnit.doHouseholds.reset();
    SetupAndParseParams();
    ASSERT_EQ(P().DoHouseholds, 1);
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










