#!/bin/bash
TESTDIR=./testcases
FILES=$TESTDIR/test*.txt
EXE=./fileCompressor

# Cleanup
rm -rf $TESTDIR/*.hcz
rm -rf $TESTDIR/*.hcz.txt
rm -rf HuffmanCodebook
rm -rf ./fileCompressor

