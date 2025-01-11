#ifndef MSHELL_H
#define MSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define BYTE unsigned char

extern char* PROMPT;

void   start_loop(void);
void   main_loop(void);
char*  read_line(void);
char** parse_line(char *);
int    execute(char **);

//Built in commands
extern int msh_cd(char **);
extern int msh_ls(char **);
extern int msh_cat(char **);
extern int msh_touch(char **);
extern int msh_rm(char **);

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

#endif
