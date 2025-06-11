#include "shell.h"

char* built_ins[] = {
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

int (*built_in_funcs[]) (char **) = {
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

unsigned int nbuiltins = sizeof(built_ins) / sizeof(char *);
