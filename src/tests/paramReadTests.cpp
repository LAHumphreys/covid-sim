#include <gtest/gtest.h>
#include "CovidSimTestFixture.h"
#include "CovidSimCmdLineArgs.h"
#include "Param.h"

class ParamReadTest: public CovidSimTestFixture {
public:
};

class PlaceClose: public ParamReadTest {};
class NetworkFile: public ParamReadTest {};

TEST_F(PlaceClose, IndepThreashold_Default) {
    CovidSimCmdLineArgs args;
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().PlaceCloseIndepThresh, 0L);
}
TEST_F(PlaceClose, IndepThreashold_Enabled) {
    CovidSimCmdLineArgs args;
    args.placeCloseIndepThreshold = "1";
    InvokeReadParam(args.BuildCmdLine());
    ASSERT_FALSE(Perr);
    ASSERT_EQ(P().PlaceCloseIndepThresh, 1L);
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
