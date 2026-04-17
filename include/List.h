#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_permissions(mode_t mode);
void print_suffix(mode_t mode); 
void print_long(char *base, char *name, int FFlag);
void list_dir(char *path, int lFlag, int aFlag, int dFlag, int FFlag);
void List(int argc, char *argv[]);