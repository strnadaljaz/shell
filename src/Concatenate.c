#include "Concatenate.h"
#include <stdio.h>
#include <string.h>

void Concatenate(int argc, char **argv) {
    int redirect = 0;
    int index;

    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i], "<")) {
            redirect = 1;
            index = i;
        }
    }

    if (redirect) {
        if (index + 1 >= argc) {
            fprintf(stderr, "No output file specified\n");
            return;
        }

        FILE *fout = fopen(argv[index + 1], "w");

        char buffer[1024];

        // Gather text from all files
        for (int i = 1; i < index; ++i) {
            FILE *file = fopen(argv[i], "r");

            while (fgets(buffer, sizeof(buffer), file) != NULL) {
                fputs(buffer, fout);
            }
            fclose(file);
        }
        fclose(fout);
    }

    else {
        for (int i = 1; i < argc; ++i) {
            FILE *file = fopen(argv[i], "r");
            char buffer[1024];

            while (fgets(buffer, sizeof(buffer), file) != NULL)
                printf("%s", buffer);

            fclose(file);
        }
    }
}
