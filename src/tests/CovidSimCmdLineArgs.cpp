//
// Created by lhumphreys on 09/05/2020.
//

#include "CovidSimCmdLineArgs.h"
#include <sstream>

std::vector<std::string> CovidSimCmdLineArgs::BuildCmdLine() const {
    std::vector<std::string> args ={
            "CovidSim",
            "/D:wpop_file",
            "/M:wpop_bin",
            "/A:sample_admin.txt",
            "/R:1.1"
    };
    const auto addOptionalArg = [&](const std::string& argSwitch, const std::optional<std::string>& argField) -> void {
        if (argField.has_value()) {
            args.push_back(std::string("/") + argSwitch + ":" + argField.value());
        }
    };
    addOptionalArg("AP", airTravelFile);
    addOptionalArg("C", placeCloseIndepThreshold);
    addOptionalArg("L", networkFileToLoad);
    addOptionalArg("O", outFileBasePath);
    addOptionalArg("P", paramFile);
    addOptionalArg("PP", preParamFile);
    addOptionalArg("S", networkFileToSave);

    std::stringstream paramName;
    for (size_t i = 0; i < NUM_CMD_LINE_PARAMS; ++i) {
        paramName.str("");
        paramName << "CLP" << (i+1);
        addOptionalArg(paramName.str(), cmdLineParam[i]);
    }

    args.push_back(setupSeeds[0]);
    args.push_back(setupSeeds[1]);
    args.push_back(runSeeds[0]);
    args.push_back(runSeeds[1]);

    return args;
}
