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
            ../Error.cpp
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
	    )


option(USE_OPENMP "Compile with OpenMP parallelism enabled" ON)
target_compile_features(CovidSim PUBLIC cxx_std_17)
target_compile_definitions(CovidSim PUBLIC UNIX)
target_include_directories(CovidSim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(CovidSim PUBLIC OpenMP::OpenMP_CXX)

add_executable(paramRead paramReadTests.cpp)
target_link_libraries(paramRead CovidSim GTest::GTest GTest::Main)

enable_testing()
add_test(paramRead paramRead)
