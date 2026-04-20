#include "List.h"

// ---------- permissions ----------
void print_permissions(mode_t mode) {
    printf(S_ISDIR(mode) ? "d" : "-");

    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");

    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");

    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

// ---------- -F ----------
void print_suffix(mode_t mode) {
    if (S_ISDIR(mode))
        printf("/");
    else if (mode & S_IXUSR)
        printf("*");
}

// ---------- -l ----------
void print_long(char *base, char *name, int FFlag) {
    struct stat st;
    char path[1024];

    snprintf(path, sizeof(path), "%s/%s", base, name);

    if (lstat(path, &st) == -1) {
        perror("lstat");
        return;
    }

    print_permissions(st.st_mode);

    printf(" %ld", st.st_nlink);

    struct passwd *pw = getpwuid(st.st_uid);
    struct group *gr = getgrgid(st.st_gid);

    printf(" %s", pw ? pw->pw_name : "?");
    printf(" %s", gr ? gr->gr_name : "?");

    printf(" %ld", st.st_size);

    char timebuf[64];
    struct tm *tm_info = localtime(&st.st_mtime);
    if (tm_info) {
        strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
        printf(" %s", timebuf);
    }

    printf(" %s", name);

    if (FFlag)
        print_suffix(st.st_mode);

    printf("\n");
}

// ---------- main listing ----------
void list_dir(char *path, int lFlag, int aFlag, int dFlag, int FFlag) {
    struct stat st;

    // -d → samo izpiši direktorij
    if (dFlag) {
        if (lstat(path, &st) == -1) {
            perror("lstat");
            return;
        }

        if (lFlag) {
            print_long(".", path, FFlag);
        } else {
            printf("%s", path);
            if (FFlag)
                print_suffix(st.st_mode);
            printf("\n");
        }
        return;
    }

    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {

        // -a
        if (!aFlag && entry->d_name[0] == '.')
            continue;

        if (lFlag) {
            print_long(path, entry->d_name, FFlag);
        } else {
            char full[1024];
            struct stat st2;

            snprintf(full, sizeof(full), "%s/%s", path, entry->d_name);
            lstat(full, &st2);

            printf("%s", entry->d_name);

            if (FFlag)
                print_suffix(st2.st_mode);

            printf("\t");
        }
    }

    if (!lFlag)
        printf("\n");

    closedir(dir);
}

// ---------- argument parsing ----------
void List(int argc, char *argv[]) {
    int lFlag = 0, aFlag = 0, dFlag = 0, FFlag = 0;
    char *path = ".";

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j]; j++) {
                if (argv[i][j] == 'l')
                    lFlag = 1;
                else if (argv[i][j] == 'a')
                    aFlag = 1;
                else if (argv[i][j] == 'd')
                    dFlag = 1;
                else if (argv[i][j] == 'F')
                    FFlag = 1;
            }
        } else {
            path = argv[i];
        }
    }

    list_dir(path, lFlag, aFlag, dFlag, FFlag);
}
