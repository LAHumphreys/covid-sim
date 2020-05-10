#include "CovidSimTestFixture.h"
#include "CovidSimExternInterface.h"
#include <regex>


void CovidSimTestFixture::CovidSimMainInitialisation() {
    ///// Flags to ensure various parameters have been read; set to false as default.
    GotAP = GotScF = 0;

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

void CovidSimTestFixture::InvokeParseCmdLine(const std::vector<std::string> &args) {

    const int argc = args.size();
    std::vector<const char*> argv;
    argv.resize(args.size());
    for (size_t i = 0; i < argc; ++i) {
        argv[i]= args[i].c_str();
    }

    ParseCmdLineArgs(argc, argv.data(),
                      ParamFile, DensityFile, NetworkFile, AirTravelFile, SchoolFile, RegDemogFile, InterventionFile, PreParamFile,
                      buf, sep, GotAP, GotScF, Perr);
}

param& CovidSimTestFixture::P() {
    return ::P;
}

char* CovidSimTestFixture::OutFile() const {
    return ::OutFile;
}

char* CovidSimTestFixture::OutFileBase() const {
    return ::OutFileBase;
}

char *CovidSimTestFixture::OutDensFile() const {
    return ::OutDensFile;
}

char *CovidSimTestFixture::AdunitFile() const {
    return ::AdunitFile;
}

void CovidSimTestFixture::InvokeSetupThreads() {
    SetupThreads();
}

void CovidSimTestFixture::InvokeReadParams() {
    ReadParams(ParamFile, PreParamFile);
}

void CovidSimTestFixture::ExpectCriticalError(
        const std::string& codeText,
        const std::function<void()> &code,
        const std::string& containsRegex)
{
    try {
        code();
        FAIL() << "Expected an exception to to be thrown when parsing: '" << codeText << "'";
    } catch (const std::exception& e) {
        const std::regex msgRegex(containsRegex);
        EXPECT_TRUE(std::regex_search(e.what(), msgRegex))
            << ">> Exception message:" << std::endl
            << e.what()
            << ">> did not contain expected message:" << std::endl
            << containsRegex;
    }
}

