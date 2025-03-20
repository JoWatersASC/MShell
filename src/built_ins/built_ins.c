#include "shell.h"

char* rel_path(char* _name, char* _path) { // return string '_path' (or './' if NULL) with '_name' appended to it so the shell can see relative to current dir
	char* path;

	if(_path) {
		path = (char *)malloc(strlen(_name) + strlen(_path) + 3);
	} else {
		path = (char *)malloc(strlen(_name) + 2);
	}
	if(!path) {
		MSHERR("Allocation error")
		return NULL;
	}

	path[0] = '.';
	path[1] = '/';
	path[2] = '\0';

	if(_path) {
		strcat(path, _path);
		strcat(path, "/");
		strcat(path, _name);
	} else {
		strcat(path, _name);
	}

	return path;
}

int msh_cd(char** args) {
    if(!args[1]) {
        MSHERR("cd: Too few arguments")
    } else if(args[2]) {
        MSHERR("cd: Too many arguments")
        return 0;
    } else {
		char* path = rel_path(args[1], NULL);

		if(!path) {
			MSHERR("Allocation error")
			return 0;
		}

        if(chdir(path)) {
            perror("MSH: chdir error");
			free(path);
            return 0;
        }
		free(path);

        char pwd[128];
        getcwd(pwd, sizeof(pwd));

        setenv("PWD", pwd, 1);
        setp_default();
    }
    
    return 1;
}

int msh_ls(char** args) {
	int fd;
	char* path = NULL;

	if(args[1]) {
		if(args[2]) {
			MSHERR("ls: Too many arguments")
			return 0;
		}
		
		path = rel_path(args[1], NULL);
		printf("%s\n", path);
		if(!path) {
			MSHERR("Allocation error")
			return 0;
		}

		fd = open(path, O_DIRECTORY | O_RDONLY);
	} else {
		fd = open(".", O_DIRECTORY | O_RDONLY);
	}

	if(fd == -1) {
		MSHERR(strerror(errno))
		return 0;
	}

	DIR* dir = fdopendir(fd);
	if(!dir) {
		MSHERR(strerror(errno))
		close(fd);
		return 0;
	}
	struct dirent* entry;

	while((entry = readdir(dir)) != NULL) {
		unsigned short rlen = entry->d_reclen;

		if(entry->d_type == DT_DIR) {
			printf("\033[34m");
		} else {
			struct stat stat_buff;
			char* e_name = rel_path(entry->d_name, path);

			if(stat(e_name, &stat_buff) == -1) {
				MSHERR(strerror(errno))
				free(e_name);
				close(fd);

				return 0;
			} else {
				if(stat_buff.st_mode & (S_IXUSR | S_IXOTH)) {
					printf("\033[38;5;87m");
				}
			}

			free(e_name);
		}

		if(*entry->d_name != '.') {
			printf("%s ", entry->d_name);
		}
		printf("\033[0m");
	}

	printf("\n");
	close(fd);

	return 1;
}

int msh_cat(char** args) {
    if(!args[1]) {
        MSHERR("cat: Too few arguments")
		return 0;
    }
	
	char** arg = args + 1;
	char buff[64] = {0};
	ssize_t bytes;

	while(*arg) {
		int fd = open(*arg, O_RDONLY);
		if(fd == -1) {
			MSHERR(strerror(errno))
			return 0;
		}
		printf("%s:\n", *arg);
		
		while((bytes = read(fd, buff, 64)) > 0) {
			write(STDOUT_FILENO, buff, bytes);
		} 
		if(bytes < 0) {
			MSHERR(strerror(errno))
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
        MSHERR("cat: Too few arguments")
    }
    
	char** arg = args + 1;

	while(*arg) {
		int fd = creat(*arg,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if(fd == -1) {
			MSHERR(strerror(errno))
			return 0;
		}

		arg++;
		close(fd);
	}

	return 1;
}

int msh_rm(char** args) {
	if(!args[1]) {
		MSHERR("cat: Too few arguments")
	}

	if(remove(args[1]) == -1) {
		MSHERR(strerror(errno))
		return 0;
	}

	return 1;
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
