#include "ChangeDirectory.h"
#include <string.h>
#include <unistd.h>

void ChangeDirectory(int argc, char **argv, char *home, char *cwd) {

    if (argc == 1) {
        if (!strcmp(argv[0], "cd"))
            chdir(home);
        else {
            int count = numberOfDots(argv[0]) / 2; // dve piki za vsako mapo višje
            for (int i = 0; i < count; ++i)
                chdir("..");
        }

    } else {
        chdir(argv[1]);
    }

    getcwd(cwd, sizeof(cwd));
}

int numberOfDots(char *string) {
    if ((string == NULL) || (!strcmp(string, "")))
        return 0;

    int count = 0;

    for (int i = 0; string[i] != '\0'; ++i) {
        if (string[i] != '.')
            return 0;
        else
            ++count;
    }

    if (count % 2 == 0)
        return count;
    else
        return 0;
}
