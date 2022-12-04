#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <utime.h>

int extract_archive() {
  return 0;
}

//main function for testing the above functions
int main() {
  char *new_dir = "new_folder";
  char *new_file = "new_file";
  int file_descriptor;
  int mkdir_result;
  struct stat filestat;
  struct utimbuf timebuf;

  timebuf.actime = 0;
  timebuf.modtime = 0;

  //Create a new file with mode 755
  file_descriptor = open(new_file, (S_IRWXU | (S_IRGRP | S_IXGRP) | (S_IROTH | S_IXOTH)));
  close(file_descriptor);

  lstat(new_file, &filestat);
  printf("new_file mtime and actime: %lu %lu\n", filestat.st_mtim.tv_sec, filestat.st_atim.tv_sec);

  utime(new_file, &timebuf);
  lstat(new_file, &filestat);
  printf("new_file mtime and actime: %lu %lu\n", filestat.st_mtim.tv_sec, filestat.st_atim.tv_sec);


  //Create a new directory with mode 755
  // mkdir_result = mkdir(new_dir, S_IRWXU | (S_IRGRP | S_IXGRP) | (S_IROTH | S_IXOTH));

  return 0;
}