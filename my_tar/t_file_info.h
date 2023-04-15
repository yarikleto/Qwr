#ifndef STRUCT_T_FILE_INFO
#define STRUCT_T_FILE_INFO
typedef struct t_file_info {
  char *name;
  __uintmax_t mode;
  uid_t uid;
  gid_t gid;
  off_t size;
  long int mtime;
  __uintmax_t chksum;
  char typeflag;
  char *linkname;
  char *magic;
  char *version;
  char *uname;
  char *gname;
  unsigned int devmajor;
  unsigned int devminor;
  char *prefix;
} t_file_info;
#endif

/* Values used in typeflag field.  */
#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* hard link */
#define SYMTYPE  '2'            /* symbolic link */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */

typedef t_file_info *file_info;

file_info t_file_constructor(void);
void t_file_destructor(file_info this);
file_info get_file_info(file_info this, char *filename);

//Initialize t_file_info variables
int t_file_initialize(file_info this);