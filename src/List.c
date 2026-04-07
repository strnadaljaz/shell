#include "List.h"
#include <dirent.h>
#include <stdio.h>

void List(int argc, char **argv, char *cwd) {
    DIR *dir = opendir(cwd);
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (!(entry->d_name[0] == '.')) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}
