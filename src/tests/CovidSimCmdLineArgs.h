#ifndef COVIDTEST_COVIDSIMCMDLINEARGS_H
#define COVIDTEST_COVIDSIMCMDLINEARGS_H
#include <string>
#include <vector>
#include <optional>

struct CovidSimCmdLineArgs {
    std::optional<std::string> airTravelFile;
    std::optional<std::string> networkFileToLoad;
    std::optional<std::string> networkFileToSave;
    std::optional<std::string> paramFile = "paramFile.txt";
    std::optional<std::string> placeCloseIndepThreshold;

    std::string runSeeds[2] = {"17389101", "4797132"};
    std::string setupSeeds[2] = {"98798150", "729101"};
    [[nodiscard]] std::vector<std::string> BuildCmdLine() const;
};


#endif //COVIDTEST_COVIDSIMCMDLINEARGS_H
