#!/bin/bash
TESTDIR_ORIG=./testcases
TESTDIR=./testcases_tmp

rm -rf HuffmanCodebook
find $TESTDIR_ORIG -type f -name "*.hcz*" -exec rm "{}" \;
find $TESTDIR_ORIG -type f -name ".gitkeep" -exec rm "{}" \;
find $TESTDIR -type f -name "*.hcz*" -exec rm "{}" \;

if [ -f ./HuffmanCodebook ]
then
  rm -rf ./HuffmanCodebook
fi
find $TESTDIR_ORIG -type f -name "*.hcz*" -exec rm "{}" \;
find $TESTDIR_ORIG -type f -name ".gitkeep" -exec rm "{}" \;
if [ -d $TESTDIR ]
then
  find $TESTDIR -type f -name "*.hcz*" -exec rm "{}" \;
fi

if [ -d $TESTDIR ]
then
  rm -rf $TESTDIR
fi  
if [ -d ./testoutput ]
then
  rm -rf ./testoutput
fi
