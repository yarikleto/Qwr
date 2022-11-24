echo DELETING CREATE_ARCHIVE.TAR, TAR1.TAR, CREATE_ARCHIVE.TXT, TAR1.TXT
rm create_archive.tar
rm tar1.tar
rm create_archive.txt
rm tar1.txt
make re
echo TEST CASE 1: tar1.tar test-3.txt tar-file.c array.c
tar -cf tar1.tar test-3.txt tar-file.c array.c
./my_tar -cf create_archive.tar test-3.txt tar-file.c array.c
cat -e tar1.tar > tar1.txt
cat -e create_archive.tar > create_archive.txt
echo DIFF TAR1.TXT AND CREATE_ARCHIVE.TXT
diff tar1.txt create_archive.txt
echo TEST CASE 1 COMPLETE

echo TEST CASE 2: tar1.tar test-3.txt tar-file.c array.c create_archive.c
rm create_archive.tar
rm tar1.tar
rm create_archive.txt
rm tar1.txt
tar -cf tar1.tar test-3.txt tar-file.c array.c create_archive.c
./my_tar -cf create_archive.tar test-3.txt tar-file.c array.c create_archive.c
cat -e tar1.tar > tar1.txt
cat -e create_archive.tar > create_archive.txt
echo DIFF TAR1.TXT AND CREATE_ARCHIVE.TXT
diff tar1.txt create_archive.txt
echo TEST CASE 2 COMPLETE
