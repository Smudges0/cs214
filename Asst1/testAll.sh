#!/bin/bash
TESTDIR_ORIG=./testcases
TESTDIR=./testcases_tmp
EXE=./fileCompressor

# Cleanup
cleanUp()
{
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
}

#-----------------------------------
# Main
#-----------------------------------
cleanUp
rm -rf $TESTDIR
rm -rf ./testoutput
# Make a copy of the original test directory so we can compare files later.
cp -R $TESTDIR_ORIG $TESTDIR
mkdir ./testoutput

# 1. Run test files in testcases dirs recursively one by one.
echo -e "Processing test files in single mode.  Dir: $TESTDIR\n"

for f in $(find $TESTDIR -type f);
do
  echo "Processing single test file: $f"

  bf=$(basename $f) # Base filename
  origf=$(echo $f| sed "s+$TESTDIR+$TESTDIR_ORIG+") # Path and filename in original testcases dir 
  fh=$f.hcz # filename with .hcz

  # 1. Build codebook
  #echo "$EXE -b $f > ./testoutput/output_b_$bf 2>&1"
  $EXE -b $f > ./testoutput/output_b_$bf 2>&1

  # 2. Compress file
  #echo "$EXE -c $f ./HuffmanCodebook > ./testoutput/output_c_$bf 2>&1"
  $EXE -c $f ./HuffmanCodebook > ./testoutput/output_c_$bf 2>&1

  # Delete file so it can be recreated by decompressing.
  rm $f

  # 3. Decompress file
  #echo "$EXE -d $fh ./HuffmanCodebook > ./testoutput/output_d_$bf 2>&1"
  $EXE -d $fh ./HuffmanCodebook > ./testoutput/output_d_$bf 2>&1

  # 4. Compare file with original. Check that new file exists.  Diff+wc will return 0 if file is missing.
  a=($(diff $f $origf | wc -l))
  lines=${a[0]}
  if [ ! -f $f ] || [ $lines -gt 0 ]
  then
    echo "Comparing: diff $f $origf: different!  ============= FAILED =============="
  else
    echo "Comparing: diff $f $origf: SUCCESS"
  fi

  echo -e
done

echo -e "\n"
cleanUp

# Do recursive test
echo -e "Processing test files in recursive mode.  Dir: $TESTDIR\n"

bdir=$(basename $TESTDIR)

# 1. Build codebook
#echo "$EXE -b $TESTDIR > ./testoutput/output_b_$TESTDIR 2>&1"
$EXE -R -b $TESTDIR > ./testoutput/output_b_$bdir 2>&1

# 2. Compress all files in dir
#echo "$EXE -c $TESTDIR ./HuffmanCodebook > ./testoutput/output_c_$TESTDIR 2>&1"
$EXE -R -c $TESTDIR ./HuffmanCodebook > ./testoutput/output_c_$bdir 2>&1

# Delete files so they can be recreated by decompressing.
find $TESTDIR -type f -not -name "*.hcz*" -exec rm "{}" \;

# 3. Decompress all files in dir
#echo "$EXE -d $TESTDIR ./HuffmanCodebook > ./testoutput/output_d_$TESTDIR 2>&1"
$EXE -R -d $TESTDIR ./HuffmanCodebook > ./testoutput/output_d_$bdir 2>&1

# 4. Loop over all text files recursively and compare with the compressed file
for f in $(find $TESTDIR -type f -not -name "*.hcz*");
do
  bf=$(basename $f) # Base filename
  origf=$(echo $f| sed "s+$TESTDIR+$TESTDIR_ORIG+") # Path and filename in original testcases dir 

  # Compare file with original.  Check that new file exists.  Diff+wc will return 0 if file is missing.
  a=($(diff $f $origf | wc -l))
  lines=${a[0]}
  if [ ! -f $f ] || [ $lines -gt 0 ]
  then
    echo "Comparing: diff $f $origf: different!  ============= FAILED =============="
  else
    echo "Comparing: diff $f $origf SUCCESS"
  fi

  echo -e
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
