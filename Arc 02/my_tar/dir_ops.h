#ifndef STRUCT_DIRENT_ENTRY
#define STRUCT_DIRENT_ENTRY
typedef struct s_dirent_entry {
  char *entry_name;
  long int t_sec;
  long int t_nsec;
} dirent_entry;
#endif

#ifndef STRUCT_DIRENT_ARRAY
#define STRUCT_DIRENT_ARRAY
typedef struct s_dirent_array {
  int size;
  struct s_dirent_entry **array;
} dirent_array;
#endif

//Sort dirent array entries
dirent_array *sort_entries(dirent_array *dirents, int tflag);

//Get each entry d_name, tv_sec, and tv_nsec values
dirent_array *get_entries(char *dir_name, dirent_array *dirents, int aflag);

//Print entry names
void print_entries(dirent_array *dirents);

//Count the number of entries in dir_name directory
int count_entries(char *dir_name, int aflag);

//Get directory entries (dirents), save them into an array of dirents
//sort the dirents, and print the dirent names 
dirent_array *get_dir_entries(dirent_array *entry_array, char *dir_name, int aflag);

//Check if a directory is found
int check_dir(char *directory);

//free dirent_array
void free_dirent_array(dirent_array *dirents);

