#include <stdio.h>
#include <sys/stat.h>
#include "MakeFile.h"

void MakeFile(int argc, char** argv) {
    if (argc < 2) {
        perror("No file name specified");
        return;
    }

    for (int i = 1; i < argc; ++i) {
        FILE *f = fopen(argv[i], "w");

        if (f == NULL) 
            perror("Error creating file");

        fclose(f);
    }
}