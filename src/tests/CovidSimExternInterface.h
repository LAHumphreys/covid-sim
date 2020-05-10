#ifndef COVIDTEST_COVIDSIMEXTERNINTERFACE_H
#define COVIDTEST_COVIDSIMEXTERNINTERFACE_H

#include <Param.h>

/*
 * CovidSim.cpp was not written to be unit tested, and instead was written as an "all in one"
 * main file.
 *
 * In order to unit test we have to:
 *   - Rename the main() function - there can only be one in the application
 *   - Treat it like a library file - and create a header file that allows us to link into it
 */

void ParseCmdLineArgs(int argc, const char **argv, char *ParamFile, char *DensityFile, char *NetworkFile,
                      char *AirTravelFile, char *SchoolFile, char *RegDemogFile,
                      char InterventionFile[][1024] , char *PreParamFile, char *buf, char *sep,
                      int &GotAP, int &GotScF, int &Perr);
void SetupThreads();

void ReadParams(char* ParamFile, char* PreParamFile);

/**
 * NOTE: Linking order is important here
 *
 * The object file that includes this inherited must be linked into the target binary
 * *after* CovidSIm.cpp itself so that they reference CovidSim's variables, and not its own
 */
extern char OutDensFile[1024];
extern char OutFileBase[1024];
extern char OutFile[1024];
extern param P;
extern char AdunitFile[1024];

#endif //COVIDTEST_COVIDSIMEXTERNINTERFACE_H
