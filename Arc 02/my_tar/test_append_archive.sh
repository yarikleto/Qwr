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
rm append_test.tar
rm my_append_test.tar
tar -rf append_test.tar fffffff.txt
./my_tar -rf my_append_test.tar fffffff.txt
echo TEST CASE 2 COMPLETE

#3. tar -rf [non-existent file] [existing file]
echo TEST CASE 3: tar -rf [non-existent file] [existing file]
rm append_test.tar
rm my_append_test.tar
tar -rf append_test.tar array.h
./my_tar -rf my_append_test.tar array.h
echo DIFF APPEND_TEST AND MY_APPEND_TEST
diff append_test.tar my_append_test.tar
echo TEST CASE 3 COMPLETE

#4. Append new entries to existing tar file
echo TEST CASE 4: APPEND NEW ENTRIES TO EXISTING TAR FILE
rm append_test.tar
rm my_append_test.tar
tar -rf append_test.tar array.h
tar -rf my_append_test.tar array.h
tar -rf append_test.tar tar-file.c
./my_tar -rf my_append_test.tar tar-file.c
echo DIFF APPEND_TEST AND MY_APPEND_TEST
diff append_test.tar my_append_test.tar
echo TEST CASE 4 COMPLETE

#5. tar -rf [existing tar file]
echo TEST CASE 5: tar -rf [existing tar file]
rm append_test.tar
rm my_append_test.tar
tar -cf append_test.tar array.c
tar -cf my_append_test.tar array.c
tar -rf append_test.tar
./my_tar -rf my_append_test.tar
echo DIFF APPEND_TEST AND MY_APPEND_TEST
diff append_test.tar my_append_test.tar
echo TEST CASE 5 COMPLETE

#6. tar -rf [existing non-tar file]
echo TEST CASE 6: tar -rf [existing NON-tar file]
rm append_test.tar
rm my_append_test.tar
tar -rf array.c > append_test.txt
git restore array.c
./my_tar -rf array.c > my_append_test.txt
git restore array.c
echo DIFF APPEND_TEST AND MY_APPEND_TEST
diff append_test.txt my_append_test.txt
echo TEST CASE 6 COMPlETE
rm append_test.txt
rm my_append_test.txt


