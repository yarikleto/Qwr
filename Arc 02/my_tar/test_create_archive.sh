rm create_archive.tar
rm tar1.tar
rm create_archive.txt
rm tar1.txt
tar -cf tar1.tar test-3.txt tar-file.c array.c
make re
./my_tar -cf create_archive.tar test-3.txt tar-file.c array.c
cat -e tar1.tar > tar1.txt
cat -e create_archive.tar > create_archive.txt
echo diff tar1.txt and create_archive.txt
diff tar1.txt create_archive.txt
