#!/bin/bash
#Append archive test cases
rm append_test.tar
rm my_append_test.tar
make re && clear

#1. tar -rf [non-existent file]
echo TEST CASE 1: tar -rf [non-existent file]
tar -rf append_test.tar
./my_tar -rf my_append_test.tar
echo DIFF APPEND_TEST AND MY_APPEND_TEST
diff append_test.tar my_append_test.tar
echo TEST CASE 1 COMPLETE

#2. tar -rf [non-existent file] [non-existent file]
echo TEST CASE 2: tar -rf [non-existent file] [non-existent file]
tar -rf my_append_test_test.tar fffffff.txt
./my_tar -rf my_append_test.tar fffffff.txt
echo TEST CASE 2 COMPLETE
