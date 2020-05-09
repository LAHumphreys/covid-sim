#include "CovidSimTestFixture.h"

void ParseCmdLineArgs(int argc, const char **argv, char *ParamFile, char *DensityFile, char *NetworkFile,
                 char *AirTravelFile, char *SchoolFile, char *RegDemogFile,
                 char InterventionFile[][1024] , char *PreParamFile, char *buf, char *sep, int i, int GotP,
                 int GotO, int GotL, int GotS, int &GotPP, int &GotAP, int &GotScF, int &Perr);

void CovidSimTestFixture::CovidSimMainInitialisation() {
    ///// Flags to ensure various parameters have been read; set to false as default.
    GotP = GotO = GotL = GotS = GotAP = GotScF = GotPP = 0;

    Perr = 0;
    fprintf(stderr, "sizeof(int)=%i sizeof(long)=%i sizeof(float)=%i sizeof(double)=%i sizeof(unsigned short int)=%i sizeof(int *)=%i\n", (int)sizeof(int), (int)sizeof(long), (int)sizeof(float), (int)sizeof(double), (int)sizeof(unsigned short int), (int)sizeof(int*));
    cl = clock();
}

void CovidSimTestFixture::SetUp() {
    CovidSimMainInitialisation();
}

void CovidSimTestFixture::InvokeReadParam(const std::vector<std::string> &args) {

    const int argc = args.size();
    std::vector<const char*> argv;
    argv.resize(args.size());
    for (size_t i = 0; i < argc; ++i) {
        argv[i]= args[i].c_str();
    }

    ParseCmdLineArgs(argc, argv.data(),
                      ParamFile, DensityFile, NetworkFile, AirTravelFile, SchoolFile, RegDemogFile, InterventionFile, PreParamFile,
                      buf, sep, i, GotP, GotO, GotL, GotS, GotPP, GotAP, GotScF, Perr);
}

extern param P;

param& CovidSimTestFixture::P() {
    return ::P;
}
