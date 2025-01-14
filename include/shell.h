#ifndef MSHELL_H
#define MSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/wait.h>

#define MSHERR(x) { fprintf(stderr, "MSH: %s\n", x); }
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
int msh_ls(char **);
int msh_cat(char **);
int msh_touch(char **);
int msh_rm(char **);
int search_built_ins(char **);

static char* built_ins[] = {
	"cd",
	"ls",
	"cat",
	"touch",
	"rm"
};
static int (*built_in_funcs[]) (char **) = {
	&msh_cd,
	&msh_ls,
	&msh_cat,
	&msh_touch,
	&msh_rm
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

#endif
