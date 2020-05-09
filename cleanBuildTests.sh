#!/bin/bash

testDir=testCovidSimBuild
srcDirRelToTestDir=../src

rm -rf $testDir
mkdir $testDir

pushd $testDir
cmake $srcDirRelToTestDir/tests || exit 1
make -j 3 || exit 1
make test


