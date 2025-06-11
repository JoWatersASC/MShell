#include "shell.h"
#include "hash.h"

extern char** environ;
extern struct ssmap alias_map;

const char* get_alias(const char* _key) {
	return get_ssval(&alias_map, _key);
}

bool set_alias(const char* _key, const char* _val) {
	const struct sspair in_pair = {_key, _val, NULL};

	return ssminsert(&alias_map, in_pair);
}

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
	if(!args[1]) { // print all aliases
		print_ssmp(&alias_map);
		return 1;
	}
	if(!args[2]) { // print alias of args[1]
		return 1;
	}

	struct sspair* alias_pair = get_ssp(&alias_map, args[1]);
	if(alias_pair) {
		alias_pair->val = args[2];
		return 1;
	}

	if(!set_alias(args[1], args[2])) {
		return 0;
	}

	return 1;
}
int msh_unalias(char** args) {
	if(!args[1]) {
		MSHERR("unalias: Too few arguments")
		return 0;
	}
	if(args[2]) {
		MSHERR("unalias: Too many arguments")
		return 0;
	}

	if(ssmremove(&alias_map, args[1])) {
		printf("Removed alias for: %s\n", args[1]);
	}

	return 1;
}

int msh_source(char** args) {
	if(!args[1]) {
		MSHERR("source: Too few arguments")
		return 0;
	}
	if(args[2]) {
		MSHERR("source: Too many arguments")
		return 0;
	}

	FILE *src_file;
	if((src_file = fopen(args[1], "r")) == NULL) {
		MSHERR(strerror(errno))
		return 0;
	}

	main_loop(src_file);
	if(fclose(src_file)) {
		printf("fclose: %s\n", strerror(errno));
	}

	return 1;
}

const char* search_aliases(const char* _alias) {
	struct sspair* alias_pair = get_ssp(&alias_map, _alias);

	if(alias_pair && strcmp(alias_pair->val, "alias") != 0) {
		return alias_pair->val;
	}

	return NULL;
}
