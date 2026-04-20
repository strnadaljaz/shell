#include "Echo.h"
#include <string.h>

void Echo(int argc, char** argv) {
    int redirect = 0;
    char* fileName = NULL;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], ">")) {
            redirect = 1;
            fileName = argv[i + 1];
            argv[i] = NULL;
            break;
        }
    }

    // pisemo v file
    if (redirect) {
        FILE *fptr;

        fptr = fopen(fileName, "a+");

        if (fptr == NULL) {
            perror("fopen");
            return;
        } 

        for (int i = 1; argv[i] != NULL; ++i) {
            fprintf(fptr, "%s", argv[i]);
            if (argv[i + 1] != NULL) 
                fprintf(fptr, " ");
        }

        fprintf(fptr, "\n");

        fclose(fptr);
    }

    else {
        for (int i = 1; argv[i] != NULL; ++i) {
            printf("%s", argv[i]);
            if (argv[i + 1] != NULL) 
                printf(" ");
        }
    }

    printf("\n");
}