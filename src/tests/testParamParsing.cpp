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

class TimeStep: public ParamParsingTest{};

TEST_F(TimeStep, ReadSteps) {
    preParams.updateTimestep = "0.25";
    SetupAndParseParams();
    ASSERT_EQ(P().TimeStep, 0.25);
}
TEST_F(TimeStep, MandatoryUpdateTimestep) {
    preParams.updateTimestep.reset();
    EXPECT_CRIT_ERROR(SetupAndParseParams(), "Unable to find .*Update timestep");
}

TEST_F(ParamParsingTest, DefaultValues) {
    SetupAndParseParams();
}











