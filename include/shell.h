#ifndef SHELL_H
#define SHELL_H

#define MAX_INPUT_LEN 1024
#define MAX_ARGS 64
#define PATH_MAX_LEN 1024
#define HOST_MAX_LEN 256

/* Prompt */
void show_prompt(void);

/* Built-in Navigation */
int builtin_cd(char **args);
int builtin_pwd(char **args);

/* Built-in File Utilities */
int builtin_cls(char **args);
int builtin_my_ls(char **args);
int builtin_my_cat(char **args);
int builtin_exit(char **args);

/* Executor */
int execute_command(char **args);

#endif /* SHELL_H */
