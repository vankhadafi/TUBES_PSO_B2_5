#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

int builtin_cd(char **args) {
    char *target = args[1];

    if (!target || strcmp(target, "~") == 0) {
        target = getenv("HOME");
        if (!target) {
            fprintf(stderr, "cd: HOME environment variable not set\n");
            return 1;
        }
    }

    if (chdir(target) != 0) {
        perror("cd");
        return 1;
    }

    return 0;
}

int builtin_pwd(char **args) {
    (void)args;
    char cwd[PATH_MAX_LEN];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        return 0;
    } else {
        perror("pwd");
        return 1;
    }
}
