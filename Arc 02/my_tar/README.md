#Welcome to My Tar
***

## Task
The task is to recreate a version of the Tar (Tape Archive) utility (my_tar).

## Description
The Tar utility is used for collecting files (archive members) into an archive 
file. The modes for my_tar are as follows:

1. -c: creating a new archive

2. -r: appending a new archive member to an existing archive or creating a new 
archive if the specified archive does not exist

3. -u: update an existing archive member if its modification date is newer than
that of its corresponding archive member.

4. -t: list tar archive file's contents

5. -x: Extract to disk from the archive file

## Installation
The executable program is my_tar. The required files are in the Program Dependencies section.

## Program Dependencies
![alt text](Dependencies.svg)

## Usage
**-c Create an archive**
<ul>
<li>./my_tar -cf [tar_file] </li>
<li>./my_tar -cf [tar_file] [item1, item2, ...]</li>
</ul>

**-t List archive contents**
<ul>
<li>./my_tar -tf [tar_file]
</ul>

**-r Append archive members**
<ul>
<li>./my_tar -rf [non-existent file]</li>
<li>./my_tar -rf [non-existent file] [non-existent file]</li>
<li>./my_tar -rf [non-existent file] [non-existent file]</li>
<li>./my_tar -rf [non-existent file] [existing file]</li>
<li>./my_tar -rf [existing file] [existing file]</li>
<li>./my_tar -rf [existing file]</li>
</ul>

**-u Update archive**

Usage is the same as -r mode with the additional functions:

<ul>
<li>./my_tar -uf [existing tar file] [newer entry]</li>
<li>./my_tar -uf [existing tar file] [newer entry] [same newer entry]</li>
</ul>

**-x Extract archive**

<ul>
<li>./my_tar -tf [tar file]</li>
<li>./mY-tar -tf [tar file] [tar_file file1, tar_file file2, ...]</li>
</ul>

## Things to Improve
1. Handle duplicate specified files

2. Make specified directories to be extracted '/' agnostic

3. List specified archive member
### The Core Team
Ricky Liu

Yaroslav Pakhaliuk
