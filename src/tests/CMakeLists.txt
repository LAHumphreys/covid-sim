project(CovidTest)

# Match the core CMake file
cmake_minimum_required (VERSION 3.8)

find_package(OpenMP REQUIRED)
find_package(GTest REQUIRED)


add_library(CovidSim
            ../binio.cpp
            ../binio.h
            ../Bitmap.cpp
            ../Bitmap.h
            ../CalcInfSusc.cpp
            ../CalcInfSusc.h
            ../Constants.h
            ../Country.h
            ../CovidSim.cpp
            ../CovidSim.h
            ../Dist.cpp
            ../Dist.h
            ../Error.h
            ../InfStat.h
            ../Kernels.cpp
            ../Kernels.h
            ../MachineDefines.h
            ../Model.h
            ../ModelMacros.h
            ../Param.h
            ../Rand.cpp
            ../Rand.h
            ../SetupModel.cpp
            ../SetupModel.h
            ../SharedFuncs.h
            ../Sweep.cpp
            ../Sweep.h
            ../Update.cpp
            ../Update.h
		    testError.cpp
	    )

option(USE_OPENMP "Compile with OpenMP parallelism enabled" ON)
target_compile_features(CovidSim PUBLIC cxx_std_17)
target_compile_definitions(CovidSim PUBLIC UNIX)
target_include_directories(CovidSim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(CovidSim PUBLIC OpenMP::OpenMP_CXX)

add_library(CovidSimTest
		ConfigFile.cpp
		ConfigFile.h
		CovidSimCmdLineArgs.cpp
		CovidSimCmdLineArgs.h
		CovidSimExternInterface.h
		CovidSimTestFixture.cpp
		CovidSimTestFixture.h
		ParamsConfigBuilder.cpp
		ParamsConfigBuilder.h
		PreParamConfigBuilder.cpp
		PreParamConfigBuilder.h
		AdunitConfigBuilder.cpp AdunitConfigBuilder.h)
target_link_libraries(CovidSimTest PUBLIC CovidSim GTest::GTest)

add_executable(testCommandLineParsing testCommandLineParsing.cpp)
target_link_libraries(testCommandLineParsing CovidSim CovidSimTest GTest::GTest GTest::Main)

add_executable(testParamParsing testParamParsing.cpp)
target_link_libraries(testParamParsing CovidSim CovidSimTest GTest::GTest GTest::Main)

enable_testing()
add_test(testCommandLineParsing testCommandLineParsing)
add_test(testParamParsing testParamParsing)
