#include <stdio.h>
#include <sys/stat.h>
#include "MakeDirectory.h"

void MakeDirectory(int argc, char* argv[]) {
    if (argc < 2) {
       perror("No directory name specified");
       return;
    }
    
    for (int i = 1; i < argc; ++i) {
        int status = mkdir(argv[i], 0755); 
        
        if (status == 1)
            perror("Error creating directory");
    }
}