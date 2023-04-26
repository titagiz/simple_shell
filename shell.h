/* LIBRARIES AND DEFINITIONS */

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* BUFFERS */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* COMMAND CHAINING */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/* STRUCTURES AND TYPE DEFINITIONS */

extern char **environ;

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* FUNCTION PROTOTYPES */

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *path_finder(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _putss(char *);
int _putchars(char);

/* errors.c */
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

/* exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory.c */
int be_free(void **);

/* atoi.c */
int interactive(info_t *);
int is_delimiter(char, char *);
int _isalpha(int);
int _atoi(char *);

/* errors1.c */
int str_toi(char *);
void print_error(info_t *, char *);
int print_decimal(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* builtin.c */
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);

/* builtin1.c */
int my_history(info_t *);
int my_alias(info_t *);

/* getline.c */
ssize_t get_input(info_t *);
int get_line(info_t *, char **, size_t *);
void sig_int_Handler(int);

/* getinfo.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environ.c */
char *get_env(info_t *, const char *);
int my_env(info_t *);
int my_set_env(info_t *);
int my_unset_env(info_t *);
int populate_env_list(info_t *);

/* getenv.c */
char **get_environ(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* Lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* lists1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_start(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* vars.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif

