#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

static void parse_line(char *line, char **args) {
    int i = 0;
    char *token = strtok(line, " \t\r\n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\r\n");
    }
    args[i] = NULL;
}

int main(void) {
    char line[MAX_INPUT_LEN];
    char *args[MAX_ARGS];

    while (1) {
        show_prompt();

        if (fgets(line, sizeof(line), stdin) == NULL) {
            /* Handle EOF (Ctrl+D) */
            printf("\n");
            break;
        }

        parse_line(line, args);

        if (args[0] == NULL) {
            continue;
        }

        execute_command(args);
    }

    return 0;
}
