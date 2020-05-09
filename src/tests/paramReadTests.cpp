#include <gtest/gtest.h>
#include "CovidSimTestFixture.h"
#include "CovidSimCmdLineArgs.h"
#include "Param.h"

class ParamReadTest: public CovidSimTestFixture {
protected:
    CovidSimCmdLineArgs args;
};

class Airports: public ParamReadTest {};
class NetworkFiles: public ParamReadTest {};
class OutFileBasePath: public ParamReadTest {};
class ParamsFile: public ParamReadTest {};
class PreParamsFile: public ParamReadTest {};
class PlaceClose: public ParamReadTest {};

TEST_F(OutFileBasePath, Specifed) {
    args.outFileBasePath = "results_";
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_STREQ(OutFileBase(), "results_");
}
TEST_F(OutFileBasePath, MandatoryField) {
    args.outFileBasePath.reset();
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_TRUE(Perr);
}

TEST_F(PreParamsFile, PreParamFileSet) {
    args.preParamFile = "testPreParams.txt";
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_STREQ(PreParamFile, "testPreParams.txt");
    ASSERT_TRUE(GotPP);
}
TEST_F(PreParamsFile, OptionalField) {
    args.preParamFile.reset();
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_FALSE(GotPP);
}

TEST_F(ParamsFile, ParamFileSet) {
    args.paramFile = "testParams.txt";
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_STREQ(ParamFile, "testParams.txt");
}
TEST_F(ParamsFile, MandatoryField) {
    args.paramFile.reset();
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_TRUE(Perr);
}

TEST_F(PlaceClose, IndepThreashold_Default) {
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().PlaceCloseIndepThresh, 0L);
}
TEST_F(PlaceClose, IndepThreashold_Enabled) {
    args.placeCloseIndepThreshold = "1";
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().PlaceCloseIndepThresh, 1L);
}

TEST_F(NetworkFiles, Default) {
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().LoadSaveNetwork, 0);
}
TEST_F(NetworkFiles, LoadFile) {
    args.networkFileToLoad = "fileToLoad";
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().LoadSaveNetwork, 1);
    ASSERT_STREQ(NetworkFile, "fileToLoad");
}
TEST_F(NetworkFiles, SaveFile) {
    args.networkFileToLoad = "fileToSave";
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().LoadSaveNetwork, 1);
    ASSERT_STREQ(NetworkFile, "fileToSave");
}
TEST_F(NetworkFiles, NotBothLoadAndSave) {
    args.networkFileToSave = "fileToSave";
    args.networkFileToLoad = "fileToLoad";
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_TRUE(Perr);
}
TEST_F(Airports, Default) {
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(GotAP, 0);
}
TEST_F(Airports, SpecifyAirportFile ) {
    args.airTravelFile = "airTravel.dat";
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(GotAP, 1);
    ASSERT_STREQ(AirTravelFile, "airTravel.dat");
}

TEST_F(ParamReadTest, DefaultArgs) {
    CovidSimCmdLineArgs args;
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
}
TEST_F(ParamReadTest, SetupSeeds) {
    CovidSimCmdLineArgs args;
    args.setupSeeds[0] = "789";
    args.setupSeeds[1] = "456";

    InvokeReadParam(args.BuildCmdLine());

    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().setupSeed1, 789);
    ASSERT_EQ(P().setupSeed2, 456);
}
TEST_F(ParamReadTest, RunTimeSeeds) {
    CovidSimCmdLineArgs args;
    args.runSeeds[0] = "123";
    args.runSeeds[1] = "456";

    InvokeReadParam(args.BuildCmdLine());

    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().runSeed1, 123);
    ASSERT_EQ(P().runSeed2, 456);
}
// TODO: Currently the commandline handler has no handling for bas seed arguments
