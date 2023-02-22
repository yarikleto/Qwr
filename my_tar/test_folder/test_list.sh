#!/bin/bash
for file in *.tar;
do echo "tar $file contents";
tar -tf "$file";
echo "my_tar $file contents";
./my_tar -tf "$file";
done
