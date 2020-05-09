#include "CovidSimTestFixture.h"

void ParseCmdLineArgs(int argc, const char **argv, char *ParamFile, char *DensityFile, char *NetworkFile,
                 char *AirTravelFile, char *SchoolFile, char *RegDemogFile,
                 char InterventionFile[][1024] , char *PreParamFile, char *buf, char *sep,
                 int &GotPP, int &GotAP, int &GotScF, int &Perr);

void SetupThreads();

void CovidSimTestFixture::CovidSimMainInitialisation() {
    ///// Flags to ensure various parameters have been read; set to false as default.
    GotAP = GotScF = GotPP = 0;

    Perr = 0;
    fprintf(stderr, "sizeof(int)=%i sizeof(long)=%i sizeof(float)=%i sizeof(double)=%i sizeof(unsigned short int)=%i sizeof(int *)=%i\n", (int)sizeof(int), (int)sizeof(long), (int)sizeof(float), (int)sizeof(double), (int)sizeof(unsigned short int), (int)sizeof(int*));
}

namespace {
    constexpr size_t CHAR_BUF_SIZE = 1024;
    param zeroInitialisedParam;
}
void CovidSimTestFixture::SetUp() {
    CovidSimMainInitialisation();
    // Make sure every tests starts with P resset to the state it would be in at program start...
    P() = ::zeroInitialisedParam;
    memset(OutDensFile(), 0, CHAR_BUF_SIZE);
    memset(OutFile(), 0, CHAR_BUF_SIZE);
    memset(OutFileBase(), 0, CHAR_BUF_SIZE);
    memset(AdunitFile(), 0, CHAR_BUF_SIZE);
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
                      buf, sep, GotPP, GotAP, GotScF, Perr);
}

extern param P;
param& CovidSimTestFixture::P() {
    return ::P;
}

extern char OutFile[1024];
char* CovidSimTestFixture::OutFile() const {
    return ::OutFile;
}

extern char OutFileBase[1024];
char* CovidSimTestFixture::OutFileBase() const {
    return ::OutFileBase;
}

extern char OutDensFile[1024];
char *CovidSimTestFixture::OutDensFile() const {
    return ::OutDensFile;
}

extern char AdunitFile[1024];
char *CovidSimTestFixture::AdunitFile() const {
    return ::AdunitFile;
}

void CovidSimTestFixture::InvokeSetupThreads() {
    SetupThreads();
}

