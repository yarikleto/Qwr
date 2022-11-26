#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "dir_ops.h"

//Sort dirent_array entries
dirent_array *sort_entries(dirent_array *dirents, int tflag) {
  int i = 1;
  int j; 
  dirent_entry *temp_ptr;

  //Sort by time modified (recent to latest)
  if(tflag == 1) {
    i = 1;
    while(i < dirents->size) {
      j = i;
      while(j > 0 && dirents->array[j-1]->t_nsec < dirents->array[j]->t_nsec) {
        temp_ptr = dirents->array[j];
        dirents->array[j] = dirents->array[j-1];
        dirents->array[j-1] = temp_ptr;
        j--;
      }
      i++;
    }
  }
  
  return dirents;
}

//Get each entry d_name, tv_sec, and tv_nsec values
//If aflag = 1, the hidden file entries are added to the dirent_array
dirent_array *get_entries(char *dir_name, dirent_array *dirents, int aflag) {
  int index = 0;
  struct stat filestat;
  struct dirent *entry;
  DIR *folder = opendir(dir_name);
  dirents->array = calloc(dirents->size + 1, sizeof(dirent_entry *));

  char *path = strdup(dir_name);
  int file_path_len = strlen(path);

  while((entry = readdir(folder)) && index < dirents->size) {
    if(aflag == 0) {
      if(strncmp(entry->d_name, ".", 1) == 0) {
        continue;
      }
    }
    
    if(strcmp(path, ".") != 0) {
      path = realloc(path, strlen(path) + strlen(entry->d_name) + 1 * sizeof(char));
      strcat(path, entry->d_name);
      lstat(entry->d_name, &filestat);
    }
    else {
      lstat(entry->d_name, &filestat);
    }

    dirents->array[index] = malloc(sizeof(dirent_entry));
    dirents->array[index]->entry_name = malloc(strlen(path) + 1 *sizeof(char));
    strcpy(dirents->array[index]->entry_name,path);

    dirents->array[index]->t_sec = filestat.st_mtim.tv_sec;
    dirents->array[index]->t_nsec = filestat.st_mtim.tv_nsec;
    index++;
    path[file_path_len] = '\0';
  }

  dirents = sort_entries(dirents, 1);
  closedir(folder);
  free(path);
  return dirents;
}

//Print entry names
void print_entries(dirent_array *dirents) {
  int index = 0;

  while(index < dirents->size) {
    write(1, dirents->array[index]->entry_name, 
          strlen(dirents->array[index]->entry_name));
    write(1, "\n", 1);
    index++;
  }
}

//Count the number of entries in the directory
//If aflag = 1, the hidden files are counted
int count_entries(char *dir_name, int aflag) {
  DIR *directory;
  int entries = 0;
  struct dirent *dir_entry;

  directory = opendir(dir_name);
  while((dir_entry = readdir(directory))) {
    if(aflag == 0) {
      if(strncmp(dir_entry->d_name,".", 1) != 0){
        entries++;
      }
    }
    else {
      entries++;
    }
  }
  closedir(directory);
  return entries;
}

//Get directory entries (dirents), save them into an array of dirents
//sort the dirents, and print the dirent names 
dirent_array *get_dir_entries(dirent_array *entry_array, char *dir_name, int aflag) {
  entry_array->size = count_entries(dir_name, aflag);
  entry_array = get_entries(dir_name, entry_array, aflag);

  //Debug: print the directory entries
  // print_entries(entry_array);
  return entry_array;
}

int check_dir(char *directory) {
  DIR *dir = opendir(directory);
  
  if(dir == NULL) {
    closedir(dir);
    return 1;
  }
  else {
    closedir(dir);
    return 0;
  }
}

void free_dirent_array(dirent_array *dirents) {
  for(int i = 0; i < dirents->size; i++) {
    free(dirents->array[i]->entry_name);
    free(dirents->array[i]);
  }
  free(dirents->array);
  free(dirents);
}

//Check if filename is in the current directory
int in_directory(char *filename) {
  DIR *folder = opendir(".");
  struct dirent *entry;

  while((entry = readdir(folder)) != NULL) {
    if(strcmp(entry->d_name, filename) == 0) {
      closedir(folder);
      return 0;
    }
  }
  closedir(folder);
  return 1;
}