#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include "t_file_info.h"
#include "helpers.h"

file_info t_file_constructor(void) {
  file_info file_ptr = malloc(sizeof(t_file_info));
  return file_ptr;
}

void t_file_destructor(file_info this) {
  free(this->name);
  free(this->linkname);
  free(this->magic);
  free(this->version);
  free(this->uname);
  free(this->gname);
  free(this->prefix);
  free(this);
}

int t_file_initialize(file_info this) {
  this->name = calloc(100, sizeof(char));
  this->mode = 0;
  this->uid = 0;
  this->gid = 0;
  this->size = 0;
  this->mtime = 0;
  this->chksum = 0;
  this->typeflag = 0;
  this->linkname = calloc(100, sizeof(char));
  this->magic = malloc(6 * sizeof(char));
  this->version = malloc(2 * sizeof(char));
  this->uname = calloc(32, sizeof(char));
  this->gname = calloc(32, sizeof(char));
  this->devmajor = 0;
  this->devminor = 0;
  this->prefix = calloc(155, sizeof(char));
  return 0;
}

file_info get_file_info(file_info this, char *filename) {
  struct stat filestat;
  struct group *group_info;
  struct passwd *passwd_info;
  int stat_result = lstat(filename, &filestat);

  if(stat_result == -1) {
    printf("Unable to get file properties\n");
  }
  else {
    group_info = getgrgid(filestat.st_gid);
    passwd_info = getpwuid(filestat.st_uid);
    this->size = (off_t)filestat.st_size;
    this->uid = (uid_t)filestat.st_uid;
    this->gid = (gid_t)filestat.st_gid;
    this->mtime = filestat.st_mtim.tv_sec;
    this->gname = strcpy(this->gname, group_info->gr_name);
    this->uname = strcpy(this->uname, passwd_info->pw_name);
    this->devmajor = major(filestat.st_rdev);
    this->devminor = minor(filestat.st_rdev);
    this->magic = strcpy(this->magic, "ustar");
    this->version = strcpy(this->version, "0");
    
    //Convert st_mode to file mode
    this->mode = filestat.st_mode & (S_ISUID | S_ISGID | S_ISVTX |S_IRWXU | S_IRWXG | S_IRWXO);

    //Set typeflag
    if(S_ISREG(filestat.st_mode)){
      this->typeflag = REGTYPE;
    }
    else if(S_ISLNK(filestat.st_mode)) {
      this->typeflag = SYMTYPE;
      this->size = 0;
    }
    else if(S_ISCHR(filestat.st_mode)) {
      this->typeflag = CHRTYPE;
    }
    else if(S_ISBLK(filestat.st_mode)) {
      this->typeflag = BLKTYPE;
    }
    else if(S_ISDIR(filestat.st_mode)) {
      this->typeflag = DIRTYPE;
      this->size = 0;
    }
    else if(S_ISFIFO(filestat.st_mode)) {
      this->typeflag = FIFOTYPE;
    }
    else {
      this->typeflag = REGTYPE;
      print_message(STDOUT_FILENO, "Warning: file type unknown\n");      
    }
    
    //Set name field
    if(this->typeflag == DIRTYPE) {
      if(filename[strlen(filename)-1] != '/') {
        strcat(filename, "/");
      }
      this->name = strcpy(this->name, filename);
    }
    else {
      this->name = strcpy(this->name, filename);
    }

    //Set linkname field
    if(this->typeflag == LNKTYPE || this->typeflag == SYMTYPE) {
      readlink(filename, this->linkname, 100);
    }

  }
  //Print t_file_info fields
  // if(stat_result != -1) {
  //   printf("Entry Name: %s\n", this->name);
  //   printf("file mode: %lo\n", this->mode);
  //   printf("uid: %o\n", this->uid);
  //   printf("gid: %o\n", this->gid);
  //   printf("size: %lo\n", this->size);
  //   printf("modification time: %lo\n", this->mtime);
  //   printf("Typeflag: %c\n", this->typeflag);
  //   printf("Link Name: %s\n", this->linkname);
  //   printf("magic: %s\n", this->magic);
  //   printf("version: %s\n", this->version);
  //   printf("User name: %s\n", this->uname);
  //   printf("Group name: %s\n", this->gname);
  //   printf("dev: %lo\n", (dev_t)filestat.st_rdev);
  //   printf("major: %o\n", this->devmajor);
  //   printf("minor: %o\n", this->devminor);
  // printf("checksum in octal: %lo\n", this->chksum);
  // printf("st_mode & S_IFMT: %d\n", filestat.st_mode & S_IFMT);

    //File type bitmask values
    // printf("S_IFMT: %d\n", S_IFMT);
    // printf("S_IFSOCK: %d\n", S_IFSOCK);
    // printf("S_IFLNK: %d\n", S_IFLNK);
    // printf("S_IFREG: %d\n", S_IFREG);
    // printf("S_IBLK: %d\n", S_IFBLK);
    // printf("S_IDIR: %d\n", S_IFDIR);
    // printf("S_ICHR: %d\n", S_IFCHR);
    // printf("S_IFIFO: %d\n", S_IFIFO);
  // }

  return this;
}

////main function for testing above functions
// int main(int argc, char **argv) {

//   //Test t_file_constructor and t_file_initialize
//   file_info file_1 = t_file_constructor();
//   t_file_initialize(file_1);

//   //Test get_file_info
//   if(argc > 1) {
//     printf("Input: %s\n", argv[1]);
//     file_1 = get_file_info(file_1, argv[1]);
//   }
//   else {
//     printf("No inputs, skipping get_file_info test\n");
//   }
  
//   t_file_destructor(file_1);
//   return 0;
// }