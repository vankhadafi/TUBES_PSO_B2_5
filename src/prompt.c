#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

void show_prompt(void) {
    char *user = getenv("USER");
    if (!user) {
        user = getlogin();
    }
    if (!user) {
        user = "user";
    }

    char hostname[HOST_MAX_LEN];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        snprintf(hostname, sizeof(hostname), "localhost");
    }

    char cwd[PATH_MAX_LEN];
    if (!getcwd(cwd, sizeof(cwd))) {
        snprintf(cwd, sizeof(cwd), "?");
    }

    /* Format spesifikasi: user@hostname:current_path> */
    printf("%s@%s:%s> ", user, hostname, cwd);
    fflush(stdout);
}
