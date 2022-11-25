#First test case: 3 regular files; tar file size = 10240 bytes
echo DELETING CREATE_ARCHIVE.TAR, TAR1.TAR, CREATE_ARCHIVE.TXT, TAR1.TXT
rm create_archive.tar
rm tar1.tar
rm create_archive.txt
rm tar1.txt
make re
# echo TEST CASE 1: tar1.tar test-3.txt tar-file.c array.c
# tar -cf tar1.tar test-3.txt tar-file.c array.c
# ./my_tar -cf create_archive.tar test-3.txt tar-file.c array.c
# cat -e tar1.tar > tar1.txt
# cat -e create_archive.tar > create_archive.txt
# echo DIFF TAR1.TXT AND CREATE_ARCHIVE.TXT
# diff tar1.txt create_archive.txt
# echo TEST CASE 1 COMPLETE

# #Second test case: 4 regular files; tar file size = 20480 bytes
# echo TEST CASE 2: tar1.tar test-3.txt tar-file.c array.c create_archive.c
# rm create_archive.tar
# rm tar1.tar
# rm create_archive.txt
# rm tar1.txt
# tar -cf tar1.tar test-3.txt tar-file.c array.c create_archive.c
# ./my_tar -cf create_archive.tar test-3.txt tar-file.c array.c create_archive.c
# cat -e tar1.tar > tar1.txt
# cat -e create_archive.tar > create_archive.txt
# echo DIFF TAR1.TXT AND CREATE_ARCHIVE.TXT
# diff tar1.txt create_archive.txt
# echo TEST CASE 2 COMPLETE

# #Third test case: 1 regular file, 1 hardlink file, 1 symbolic link file
# echo TEST CASE 3: tar1.tar test-3.txt test-3-hardlink test-3-symboliclink.txt
# rm create_archive.tar
# rm tar1.tar
# rm create_archive.txt
# rm tar1.txt
# tar -cf tar1.tar test-3.txt test-3-hardlink test-3-symboliclink.txt
# ./my_tar -cf create_archive.tar test-3.txt test-3-hardlink test-3-symboliclink.txt
# cat -e tar1.tar > tar1.txt
# cat -e create_archive.tar > create_archive.txt
# echo DIFF TAR1.TXT AND CREATE_ARCHIVE.TXT
# diff tar1.txt create_archive.txt
# echo TEST CASE 3 COMPLETE

# #Fourth test case: 1 directory
# echo TEST CASE 4: tar1.tar test_folder
# rm create_archive.tar
# rm tar1.tar
# rm create_archive.txt
# rm tar1.txt
# tar -cf tar1.tar test_folder
# ./my_tar -cf create_archive.tar test_folder
# cat -e tar1.tar > tar1.txt
# cat -e create_archive.tar > create_archive.txt
# echo DIFF TAR1.TXT AND CREATE_ARCHIVE.TXT
# diff tar1.txt create_archive.txt
# echo TEST CASE 4 COMPLETE

# #Fifth test case: 1 regular file and 1 directory 
# echo TEST CASE 5: tar1.tar test-3.txt test_folder
# rm create_archive.tar
# rm tar1.tar
# rm create_archive.txt
# rm tar1.txt
# tar -cf tar1.tar test-3.txt test_folder
# ./my_tar -cf create_archive.tar test-3.txt test_folder 
# cat -e tar1.tar > tar1.txt
# cat -e create_archive.tar > create_archive.txt
# echo DIFF TAR1.TXT AND CREATE_ARCHIVE.TXT
# diff tar1.txt create_archive.txt
# echo TEST CASE 5 COMPLETE

#Sixth test case: 1 directory and 1 regular file
echo TEST CASE 6: tar1.tar test_folder test-3.txt
rm create_archive.tar
rm tar1.tar
rm create_archive.txt
rm tar1.txt
tar -cf tar1.tar test_folder test-3.txt
./my_tar -cf create_archive.tar test_folder test-3.txt
cat -e tar1.tar > tar1.txt
cat -e create_archive.tar > create_archive.txt
echo DIFF TAR1.TXT AND CREATE_ARCHIVE.TXT
diff tar1.txt create_archive.txt
echo TEST CASE 6 COMPLETE
