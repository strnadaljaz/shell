#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Sleep.h"

void Sleep(int argc, char** argv) {
    if (argc != 2) {
        perror("Wrong number of arguments");
        return;
    }

    char* endptr;

    int num = strtol(argv[1], &endptr, 10); 

    sleep(num); 
}