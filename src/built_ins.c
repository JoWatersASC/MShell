#include "shell.h"

int msh_cd(char** args) {
    if(!args[1]) {
        MSHERR("cd: Too few arguments");
    } else if(args[2]) {
        MSHERR("cd: Too many arguments")
        return 0;
    }else {
        if(chdir(args[1])) {
            perror("MSH: chdir error");
            return 0;
        }
        char pwd[128];
        getcwd(pwd, sizeof(pwd));

        setenv("PWD", pwd, 1);
        setp_default();
    }
    
    return 1;
}

int msh_ls(char** args) {
	if(!args[1]) {
		int fd = open(".", O_DIRECTORY | O_RDONLY);
		if(fd == -1) {
			MSHERR(strerror(errno));
			return 0;
		}
	
		DIR* dir = fdopendir(fd);
		struct dirent* entry;

		while((entry = readdir(dir)) != NULL) {
			unsigned short rlen = entry->d_reclen;
			
			if(entry->d_type == DT_DIR) {
				printf("\033[34m");
			}
			
			if(*entry->d_name != '.') {
				printf("%s ", entry->d_name);
			}
			printf("\033[0m");
		}

		printf("\n");
		close(fd);
	}
	return 1;
}

int msh_cat(char** args) {
    if(!args[1]) {
        MSHERR("cat: Too few arguments");
    }
	
	char** arg = args + 1;

	char buff[64] = {0};
	ssize_t bytes;

	while(*arg) {
		int fd = open(*arg, O_RDONLY);
		if(fd == -1) {
			MSHERR(strerror(errno));
			return 0;
		}
		printf("%s:\n", *arg);
		
		while((bytes = read(fd, buff, 64)) > 0) {
			write(STDOUT_FILENO, buff, bytes);
		} 
		if(bytes < 0) {
			MSHERR(strerror(errno));
			return 0;
		}

		printf("\n");
		arg++;
		memset(buff, 0, 64);
		close(fd);
	} 

	return 1;
}

int msh_touch(char** args) {
    if(!args[1]) {
        MSHERR("cat: Too few arguments");
    }
    
	char** arg = args + 1;

	while(*arg) {
		int fd = creat(*arg,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if(fd == -1) {
			MSHERR(strerror(errno));
			return 0;
		}

		arg++;
		close(fd);
	}

	return 1;
}

int msh_rm(char** args) {
    return 0;
}

int search_built_ins(char** args) {
    BYTE num_built_ins = sizeof(built_ins) / sizeof(char *); // number of built in functions

    for(int i = 0; i < num_built_ins; i++) {
        if(strcmp(args[0], built_ins[i]) == 0) {
            return (*built_in_funcs[i])(args);
        }
    }

    return -1;
}
