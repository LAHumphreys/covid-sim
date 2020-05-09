//
// Created by lhumphreys on 09/05/2020.
//

#include "CovidSimCmdLineArgs.h"

std::vector<std::string> CovidSimCmdLineArgs::BuildCmdLine() const {
    std::vector<std::string> args ={
            "/C:1",
            "/PP:preUK_R0=2.0.txt",
            "/P:p_NoInt.txt",
            "/CLP1:100000",
            "/CLP2:0",
            "/O:NoInt_R0=2.2",
            "/D:wpop_file",
            "/M:wpop_bin",
            "/A:sample_admin.txt",
            "/S:NetworkUKN_32T_100th.bin",
            "/R:1.1"
    };
    args.push_back(setupSeeds[0]);
    args.push_back(setupSeeds[1]);
    args.push_back(runSeeds[0]);
    args.push_back(runSeeds[1]);

    return args;
}
