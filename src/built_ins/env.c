#include "shell.h"

extern char** environ;

int msh_set(char** args) {
	if(!args[1]) {
		char** env = environ;
		while(*env) {
			printf("%s\n", *env);
			env++;
		}

		return 1;
	}

	if(!args[2]) { // means a first arg(env var name) was passed but wasn't given anything to set it to
		MSHERR("set: Too many arguments")
		return 0;
	}

	if(setenv(args[1], args[2], 1) == -1) {
		MSHERR(strerror(errno))
		return 0;
	}

	return 1;	
}
int msh_unset(char** args) {
	if(!args[1]) {
		MSHERR("unset: Too few arguments")
		return 0;
	}

	if(unsetenv(args[1]) == -1) {
		MSHERR(strerror(errno))
		return 0;
	}

	return 1;
}

int msh_alias(char** args) {
	return 1;
}
int msh_unalias(char** args) {
	return 1;
}

int msh_source(char** args) {
	return 1;
}
