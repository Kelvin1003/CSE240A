#! /bin/bash

make ../src

test_file_name=$1.txt

echo "$test_file_name" > $test_file_name
echo " " >> $test_file_name

for test in "fp_1.bz2" "fp_2.bz2" "int_1.bz2" "int_2.bz2" "mm_1.bz2" "mm_2.bz2"
do
    echo "Test: $test" >> $test_file_name
    bunzip2 -kc ../traces/$test | ../src/predictor --$1 >> $test_file_name
    echo " " >> $test_file_name
done