#include "shell.h"

#define LBUFF_LEN 64 // Default size of line buffer
#define LTOK_NUM  8

char* PROMPT = NULL;

static const char delims[] = " \r\a";
extern char** environ;

void* reallocate(void *, size_t, size_t);

void start_loop(void) {
	main_loop();
}

void main_loop(void) {
	char* input;
	char** argl;
	int status;

	setp_default();
	do {
		printf("%s", PROMPT);
		// get line
		input = read_line();
		// parse line
		argl = parse_line(input);
		// execute line
		// set status
		status = execute(argl);

		free(input);
		free(argl);
	} while(status != 0);

}

char* read_line(void) {
	char c;
	int pos = 0;
	short buff_len = LBUFF_LEN;
	char* buff = (char *)malloc(buff_len * sizeof(char));

	if(!buff) {
		printf("MSH: Line buffer allocation error\n");
		exit(1);
	}

	while(true) {
		c = getc(stdin);

		if(c == -1)
			exit(0);
		if(c == '\r' || c == '\n') {
			buff[pos] = '\0';
			return buff;
		}

		if(pos >= buff_len - 1) { // At end of buffer, allocate more space
			buff_len += LBUFF_LEN * 2 / 3;

			char* new_buff = (char *)malloc(buff_len * sizeof(char));
			if(!new_buff) {
				printf("MSH: Line buffer allocation error\n");
				exit(1);
			}

			memcpy(new_buff, buff, pos);
			free(buff);

			buff = new_buff;
		}

		buff[pos++] = c;
	}

	return NULL;
}

char** parse_line(char* line) {
	short buff_len = LTOK_NUM;
	short pos = 0;
	char* token;
	char** out = (char **)malloc(buff_len * sizeof(char *));

	if(!out) {
		printf("MSH: Token buffer allocation error\n");
		exit(1);
	}
	
	token = strtok(line, delims);
	while(token) {
		out[pos++] = token;
		
		if(pos >= buff_len) {
			size_t new_len = buff_len + LTOK_NUM;
			char** temp = out;

			out = (char **)malloc(new_len * sizeof(char *));
			if(!out) {
				printf("MSH: Token buffer allocation error\n"); 
				exit(1);
			}
			memcpy(out, temp, buff_len * sizeof(char *));

			free(temp);
			buff_len = new_len;

			return out;
		}

		token = strtok(NULL, delims);
	}

	out[pos] = NULL;
	return out;
}

int run(char** tokens) {
	pid_t pid;
	int status;

	pid = fork();
	if(pid == 0) {
		if(execvp(tokens[0], tokens) == -1) {
			perror("MSH: Process execution failure");
		}
		exit(1);
	} else if(pid < 0) {
		perror("MSH: Fork error");
	} else {
		do {
			waitpid(pid, &status, 0);
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

int execute(char** argl) {
	if(argl[0] == NULL) {
		return 1;
	}

	int i = search_built_ins(argl);
	if(i != -1)
		return i;

	return run(argl);
}

void* reallocate(void* ptr, const size_t old, const size_t new) {
	if(new == 0) {
		free(ptr);
		return NULL;
	}

	void* temp = ptr;
	ptr = malloc(new);

	if(!ptr) {
		return temp;
	}

	if(temp) {
		size_t copy_num = old < new ? old : new;
		memcpy(ptr, temp, copy_num);
	}

	free(temp);
	return ptr;
}

void setp_default() {
	char* USER;
	char* PATH;

	USER = getenv("USER");
	PATH = getenv("PWD");

	PROMPT = (char *)calloc(256, sizeof(char));

	strcat(PROMPT, "\033[38;5;100m");
	strcat(PROMPT, USER);
	strcat(PROMPT, ":\033[32m");
	strcat(PROMPT, PATH);
	strcat(PROMPT, "\n\033[36m$ \033[0m\0");
}