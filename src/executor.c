#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

int builtin_exit(char **args) {
    (void)args;
    exit(0);
}

int execute_command(char **args) {
    if (args[0] == NULL) {
        return 0;
    }

    /* Built-in Navigation */
    if (strcmp(args[0], "cd") == 0) {
        return builtin_cd(args);
    }
    if (strcmp(args[0], "pwd") == 0) {
        return builtin_pwd(args);
    }

    /* Built-in Utilities */
    if (strcmp(args[0], "cls") == 0 || strcmp(args[0], "clear") == 0) {
        return builtin_cls(args);
    }
    if (strcmp(args[0], "my_ls") == 0) {
        return builtin_my_ls(args);
    }
    if (strcmp(args[0], "my_cat") == 0) {
        return builtin_my_cat(args);
    }
    if (strcmp(args[0], "exit") == 0) {
        return builtin_exit(args);
    }

    /* External Commands via POSIX Process API */
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        /* Child Process */
        if (execvp(args[0], args) == -1) {
            perror(args[0]);
        }
        exit(EXIT_FAILURE);
    } else {
        /* Parent Process */
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}
