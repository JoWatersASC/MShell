#ifndef MSHELL_H
#define MSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

// #define MSHERR(x) { fprintf(stderr, "MSH: %s\n", x); }
#define MSHLOG(x) { printf("MSH: %s\n", x); }
#define BYTE unsigned char

extern char* PROMPT;

void   start_loop(void);
void   main_loop(void);
char*  read_line(void);
char** parse_line(char *);
int    run(char **);
int    execute(char **);

//Built in commands
int msh_cd(char **);
int msh_pwd(char **);
int msh_ls(char **);
int msh_cat(char **);
int msh_touch(char **);
int msh_rm(char **);

//Environment control
int msh_set(char **);
int msh_unset(char **);
int msh_alias(char **);
int msh_unalias(char **);
int msh_source(char **);

int search_built_ins(char **);

static char* built_ins[] = {
	"cd",
	"ls",
	"cat",
	"touch",
	"rm",

	"set", //a.k.a. 'export'
	"unset",
	"alias",
	"unalias",
	"source" // sometimes can also just say '.'
};
static int (*built_in_funcs[]) (char **) = {
	&msh_cd,
	&msh_ls,
	&msh_cat,
	&msh_touch,
	&msh_rm,

	&msh_set,
	&msh_unset,
	&msh_alias,
	&msh_unalias,
	&msh_source
};
static int get_argc(void** argv) {
	void** arg = argv;
	int out = 0;

	while(arg && *arg) {
		out++;
		arg++;
	}

	return out;
}

void setp_default();

#define MSHERR(x) do { \
	time_t rawtime; \
	struct tm * timeinfo; \
	char timestamp[20]; \
	time(&rawtime); \
	timeinfo = localtime(&rawtime); \
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo); \
	fprintf(stderr, "[%s] [%s:%d %s()] ", timestamp, __FILE__, __LINE__, __func__); \
	fprintf(stderr, "%s\n", x); \
	fflush(stderr); /* Important for immediate output */ \
} while(0);

#endif
