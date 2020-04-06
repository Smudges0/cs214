#!/bin/bash
TESTDIR=./testcases
FILES=$TESTDIR/test*.txt
EXE=./fileCompressor

# Cleanup
rm -rf $TESTDIR/*.hcz
rm -rf $TESTDIR/*.hcz.txt
rm -rf HuffmanCodebook
rm -rf ./testoutput


mkdir ./testoutput

# build, compress, decompress and compare.
for f in $FILES
do
  echo "Processing test file $f"
  # take action on each file. $f store current file name
  bf=$(basename $f)
  #fh=${f%.txt}.hcz // Replaces .txt with .hcz - Not what the program does...
  fh=$f.hcz

  #echo "$EXE -b $f > ./testoutput/output_b_$bf 2>&1"
  $EXE -b $f > ./testoutput/output_b_$bf 2>&1

  #echo "$EXE -c $f ./HuffmanCodebook > ./testoutput/output_c_$bf 2>&1"
  $EXE -c $f ./HuffmanCodebook > ./testoutput/output_c_$bf 2>&1

  #echo "$EXE -d $fh ./HuffmanCodebook > ./testoutput/output_d_$bf 2>&1"
  $EXE -d $fh ./HuffmanCodebook > ./testoutput/output_d_$bf 2>&1

  echo "Comparing: diff $f $fh.txt"
  diff $f $fh.txt

  #diff output_i_$bf expected_i_$bf

  echo -e "\n"
done

# echo "Testing bad arguments: No args"
# ../a.out > output_noargs.txt 2>&1

# echo "Testing bad arguments: No sort type arg"
# ../a.out test0.txt > output_nosorttypearg.txt 2>&1

# echo "Testing bad arguments: Invalid sort type"
# ../a.out -g test0.txt > output_noinvalidsorttype.txt 2>&1

# echo "Testing bad arguments: No file name arg"
# ../a.out -i > output_nofilenamearg.txt 2>&1

# echo "Testing bad arguments: No file"
# ../a.out -i missingFile.txt > output_nofile.txt 2>&1
