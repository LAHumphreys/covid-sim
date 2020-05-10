#include <gtest/gtest.h>
#include "CovidSimTestFixture.h"
#include "CovidSimCmdLineArgs.h"

class CommandLineParsingTest: public CovidSimTestFixture {
protected:
    CovidSimCmdLineArgs args;
};

namespace {
    class AdminFile: public CommandLineParsingTest {};
    class Airports: public CommandLineParsingTest {};
    class CommandLineParams: public CommandLineParsingTest {};
    class DensityFiles: public CommandLineParsingTest {};
    class Kernel: public CommandLineParsingTest {};
    class MaxThreads: public CommandLineParsingTest {};
    class NetworkFiles: public CommandLineParsingTest {};
    class OutFileBasePath: public CommandLineParsingTest {};
    class ParamsFile: public CommandLineParsingTest {};
    class PlaceClose: public CommandLineParsingTest {};
    class PreParamsFile: public CommandLineParsingTest {};
    class R0Scale: public CommandLineParsingTest {};
}

TEST_F(Kernel, Optional) {
    args.kernelOffsetScale.reset();
    args.kernelPowerScale.reset();
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().KernelOffsetScale, 1);
    ASSERT_EQ(P().KernelPowerScale, 1);
}
TEST_F(Kernel, Specified) {
    args.kernelOffsetScale = "1.5";
    args.kernelPowerScale = "2.5";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().KernelOffsetScale, 1.5);
    ASSERT_EQ(P().KernelPowerScale, 2.5);
}
TEST_F(MaxThreads, Optional) {
    args.maxThreads.reset();
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().MaxNumThreads, 0);
}
TEST_F(MaxThreads, Specified) {
    args.maxThreads = "2";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().MaxNumThreads, 2);
}

TEST_F(AdminFile, Specified) {
    args.adminFile = "adminFile.txt";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_STREQ(AdunitFile(), "adminFile.txt");
}
TEST_F(AdminFile, Optional) {
    args.adminFile.reset();
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(AdunitFile()[0], 0);
}

TEST_F(CommandLineParams, AllProvided) {
    args.cmdLineParam[0] = "1.0";
    args.cmdLineParam[1] = "1.1";
    args.cmdLineParam[2] = "1.2";
    args.cmdLineParam[3] = "1.3";
    args.cmdLineParam[4] = "1.4";
    args.cmdLineParam[5] = "1.5";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_FLOAT_EQ(P().clP1, 1.0);
    ASSERT_FLOAT_EQ(P().clP1, 1.0);
    ASSERT_FLOAT_EQ(P().clP2, 1.1);
    ASSERT_FLOAT_EQ(P().clP3, 1.2);
    ASSERT_FLOAT_EQ(P().clP4, 1.3);
    ASSERT_FLOAT_EQ(P().clP5, 1.4);
    ASSERT_FLOAT_EQ(P().clP6, 1.5);
}
TEST_F(CommandLineParams, NoneProvided) {
    args.cmdLineParam[0].reset();
    args.cmdLineParam[1].reset();
    args.cmdLineParam[2].reset();
    args.cmdLineParam[3].reset();
    args.cmdLineParam[4].reset();
    args.cmdLineParam[5].reset();
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_FLOAT_EQ(P().clP1, 0.0);
    ASSERT_FLOAT_EQ(P().clP1, 0.0);
    ASSERT_FLOAT_EQ(P().clP2, 0.0);
    ASSERT_FLOAT_EQ(P().clP3, 0.0);
    ASSERT_FLOAT_EQ(P().clP4, 0.0);
    ASSERT_FLOAT_EQ(P().clP5, 0.0);
    ASSERT_FLOAT_EQ(P().clP6, 0.0);
}

TEST_F(DensityFiles, OptionalField) {
    args.densityFile.reset();
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().DoHeteroDensity, 0);
}
TEST_F(DensityFiles, SpecifiedFile) {
    args.densityFile = "density.dat";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().DoHeteroDensity, 1);
    ASSERT_EQ(P().DoPeriodicBoundaries, 0);
    ASSERT_STREQ(DensityFile, "density.dat");
}
TEST_F(DensityFiles, OutputOptional) {
    args.densityOutputFile.reset();
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().OutputDensFile, 0);
}
TEST_F(DensityFiles, OutputSpecified) {
    args.densityOutputFile = "outputDensity.dat";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().OutputDensFile, 1);
    ASSERT_STREQ(OutDensFile(), "outputDensity.dat");
}

TEST_F(OutFileBasePath, Specifed) {
    args.outFileBasePath = "results_";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_STREQ(OutFileBase(), "results_");
    ASSERT_STREQ(OutFile(), "results_");
}
TEST_F(OutFileBasePath, MandatoryField) {
    args.outFileBasePath.reset();
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_TRUE(Perr);
}

TEST_F(PreParamsFile, PreParamFileSet) {
    args.preParamFile = "testPreParams.txt";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_STREQ(PreParamFile, "testPreParams.txt");
}
TEST_F(PreParamsFile, OptionalField) {
    args.paramFile = "params.txt";
    args.preParamFile.reset();
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_STREQ(PreParamFile, "../Pre_params.txt");
}

TEST_F(ParamsFile, ParamFileSet) {
    args.paramFile = "testParams.txt";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_STREQ(ParamFile, "testParams.txt");
}
TEST_F(ParamsFile, MandatoryField) {
    args.paramFile.reset();
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_TRUE(Perr);
}

TEST_F(PlaceClose, IndepThreashold_Default) {
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().PlaceCloseIndepThresh, 0L);
}
TEST_F(PlaceClose, IndepThreashold_Enabled) {
    args.placeCloseIndepThreshold = "1";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().PlaceCloseIndepThresh, 1L);
}

TEST_F(NetworkFiles, Default) {
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().LoadSaveNetwork, 0);
}
TEST_F(NetworkFiles, LoadFile) {
    args.networkFileToLoad = "fileToLoad";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().LoadSaveNetwork, 1);
    ASSERT_STREQ(NetworkFile, "fileToLoad");
}
TEST_F(NetworkFiles, SaveFile) {
    args.networkFileToLoad = "fileToSave";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().LoadSaveNetwork, 1);
    ASSERT_STREQ(NetworkFile, "fileToSave");
}
TEST_F(NetworkFiles, NotBothLoadAndSave) {
    args.networkFileToSave = "fileToSave";
    args.networkFileToLoad = "fileToLoad";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_TRUE(Perr);
}
TEST_F(Airports, Default) {
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(GotAP, 0);
}
TEST_F(Airports, SpecifyAirportFile ) {
    args.airTravelFile = "airTravel.dat";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(GotAP, 1);
    ASSERT_STREQ(AirTravelFile, "airTravel.dat");
}
TEST_F(R0Scale, Optional) {
    args.r0.reset();
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().R0scale, 1.0);
}
TEST_F(R0Scale, Specified) {
    args.r0 = "2.3";
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_FLOAT_EQ(P().R0scale, 2.3);
}

TEST_F(CommandLineParsingTest, DefaultArgs) {
    InvokeParseCmdLine(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
}
TEST_F(CommandLineParsingTest, SetupSeeds) {
    args.setupSeeds[0] = "789";
    args.setupSeeds[1] = "456";

    InvokeParseCmdLine(args.BuildCmdLine());

    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().setupSeed1, 789);
    ASSERT_EQ(P().setupSeed2, 456);
}
TEST_F(CommandLineParsingTest, RunTimeSeeds) {
    args.runSeeds[0] = "123";
    args.runSeeds[1] = "456";

    InvokeParseCmdLine(args.BuildCmdLine());

    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().runSeed1, 123);
    ASSERT_EQ(P().runSeed2, 456);
}
