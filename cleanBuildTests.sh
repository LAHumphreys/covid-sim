#!/bin/bash

testDir=testCovidSimBuild
srcDirRelToTestDir=../src
depsDir="deps"
installDir="$depsDir/install"

function InstallGTest {
    installTarget=$1

    if [[ -e googletest ]]; then
        pushd googletest
            git pull || exit 1
        popd
    else
        git clone https://github.com/google/googletest.git || exit 1
    fi
    mkdir -p googletest/build || exit 1
    pushd googletest/build || exit 1
        cmake -DCMAKE_BUILD_TYPE=Release "-DCMAKE_INSTALL_PREFIX:PATH=$installTarget" .. || exit 1
        make -j 3 || exit 1
        make install || exit 1
    popd || exit 1

}

function InstallDeps {
    mkdir -p $depsDir
    mkdir -p $installDir

    pushd $installDir || exit 1
        fullInstallDir=$PWD
    popd || exit 1

    pushd $depsDir || exit 1
        InstallGTest $fullInstallDir
    popd || exit 1
}

function DoTests {
    pushd $installDir || exit 1
        fullInstallDir=$PWD
    popd || exit 1
    MODULE_PATH="$fullInstallDir/lib/cmake"
    PREFIX_PATH="$fullInstallDir/lib/cmake"
    INSTALL_PATH="$fullInstallDir"

    cmake -DCMAKE_MODULE_PATH:PATH=$MODULE_PATH -DCMAKE_PREFIX_PATH:PATH=$PREFIX_PATH -DCMAKE_INSTALL_PREFIX:PATH=$INSTALL_PATH $srcDirRelToTestDir/tests || exit 1
    make -j 3 || exit 1
    make test || exit 1
}

if [[ "$1" == "-deepClean" ]]; then
    rm -rf $testDir
fi

mkdir -p $testDir
pushd $testDir || exit 1
    InstallDeps
    DoTests
popd || exit 1



