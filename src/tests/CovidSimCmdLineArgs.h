#ifndef COVIDTEST_COVIDSIMCMDLINEARGS_H
#define COVIDTEST_COVIDSIMCMDLINEARGS_H
#include <string>
#include <vector>

struct CovidSimCmdLineArgs {
    std::string setupSeeds[2] = {"98798150", "729101"};
    std::string runSeeds[2] = {"17389101", "4797132"};
    [[nodiscard]] std::vector<std::string> BuildCmdLine() const;
};


#endif //COVIDTEST_COVIDSIMCMDLINEARGS_H
