#!/bin/bash
FILES=test*.txt
for f in $FILES
do
  echo "Processing test file $f"
  # take action on each file. $f store current file name
  bf=$(basename $f)
  ../a.out -i $f > output_i_$bf 2>&1
  diff output_i_$bf expected_i_$bf
 
  ../a.out -q $f > output_q_$bf 2>&1
  diff output_q_$bf expected_q_$bf
done

echo "Testing bad arguments: No args"
../a.out > output_noargs.txt 2>&1

echo "Testing bad arguments: No sort type arg"
../a.out test0.txt > output_nosorttypearg.txt 2>&1

echo "Testing bad arguments: Invalid sort type"    
../a.out -g test0.txt > output_noinvalidsorttype.txt 2>&1

echo "Testing bad arguments: No file name arg" 
../a.out -i > output_nofilenamearg.txt 2>&1

echo "Testing bad arguments: No file"
../a.out -i missingFile.txt > output_nofile.txt 2>&1 
