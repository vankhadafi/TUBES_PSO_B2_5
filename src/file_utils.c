#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include "shell.h"

int builtin_cls(char **args) {
    (void)args;
    /* ANSI Escape Sequence: clear screen + reset cursor */
    const char *clear_seq = "\033[H\033[J";
    write(STDOUT_FILENO, clear_seq, 7);
    return 0;
}

int builtin_my_ls(char **args) {
    const char *dir_path = ".";
    if (args[1] != NULL) {
        dir_path = args[1];
    }

    DIR *d = opendir(dir_path);
    if (!d) {
        perror("my_ls");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        /* Lewati hidden files jika tidak diminta */
        if (entry->d_name[0] == '.') {
            continue;
        }
        printf("%s  ", entry->d_name);
    }
    printf("\n");

    closedir(d);
    return 0;
}

int builtin_my_cat(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "my_cat: argumen file diperlukan\nContoh: my_cat nama_file.txt\n");
        return 1;
    }

    for (int i = 1; args[i] != NULL; i++) {
        int fd = open(args[i], O_RDONLY);
        if (fd < 0) {
            perror("my_cat");
            continue;
        }

        char buffer[1024];
        ssize_t bytes_read;
        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            ssize_t bytes_written = 0;
            while (bytes_written < bytes_read) {
                ssize_t w = write(STDOUT_FILENO, buffer + bytes_written, bytes_read - bytes_written);
                if (w < 0) {
                    perror("my_cat: write");
                    break;
                }
                bytes_written += w;
            }
        }

        if (bytes_read < 0) {
            perror("my_cat: read");
        }

        close(fd);
    }

    return 0;
}
