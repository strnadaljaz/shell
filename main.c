#include <dirent.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "List.h"
#include "ChangeDirectory.h"
#define MAX_ARGS 64

/* TODO:
 * .help za izpis vseh moznih ukazov in kaj naredijo
 *
 *
 *
 */

int main(void) {
    system("clear");

    // Dobim hostname
    char hostname[1024];
    gethostname(hostname, sizeof(hostname));

    // Pomaknem se v domačo datoteko
    chdir(getenv("HOME"));

    // Spremenljivka za izpisovanje trenutne datoteke
    char cwd[256];

    // Spremenljivke za uporabnikov vnos
    char *input = NULL;
    size_t len = 0; // buffer size
    ssize_t read;   // number of charachters

    // argv in argc
    char *argv[MAX_ARGS];
    int argc = 0;

    while (true) {
        getcwd(cwd, sizeof(cwd));

        printf("%s@shell -> ", hostname);
        printf("%s ", cwd);

        read = getline(&input, &len, stdin);
        if (read == -1)
            break;

        // odstranim \n na koncu inputa
        input[strcspn(input, "\n")] = '\0';

        argc = 0;
        // dobim prvo besedo v inputu
        char *token = strtok(input, " ");

        while (token != NULL && argc < MAX_ARGS - 1) {
            argv[argc++] = token;
            token = strtok(NULL, " "); // null pomeni: nadaljuj kjer si ostal
        }

        argv[argc] = NULL;

        if (argc == 0)
            continue; // Če je uporabnik samo stisnil enter, gremo na začetek
                      // loopa

        // ukaz clear
        if (!strcmp(argv[0], "cl"))
            system("clear");

        // ukaz exit
        else if (!strcmp(argv[0], "exit"))
            break;

        // ukaz change directory
        else if ((!strcmp(argv[0], "cd") || ((numberOfDots(argv[0]) % 2 == 0) && (numberOfDots(argv[0]) != 0)))) {
            ChangeDirectory(argc, argv, getenv("HOME"), cwd);  
        }

        // Ukaz list
        else if (!strcmp(argv[0], "ls")) {
            List(argc, argv, cwd);
        }

        // Ukaz help
        else if (!strcmp(argv[0], ".help")) {
            
        }        

        else {
            printf("Command %s not found. Run .help for all available commands\n", argv[0]);
        }
    }

    return 0;
}
