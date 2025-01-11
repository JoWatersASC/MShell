#include "shell.h"

#define LBUFF_LEN 64 // Default size of line buffer
#define LTOK_NUM  8
#define LOG printf("%s\n", PROMPT);

static char* USER;
static char* PATH;
char* PROMPT = NULL;


void start_loop(void) {
	USER = getenv("USER");
	PATH = getenv("PWD");

	PROMPT = (char *)calloc(256, sizeof(char));

	strcat(PROMPT, "\033[38;5;100m");
	strcat(PROMPT, USER);
	strcat(PROMPT, ":\033[32m");
	strcat(PROMPT, PATH);
	strcat(PROMPT, "\n\033[36m$ \033[0m");

	main_loop();
}

void main_loop(void) {
	char* input;
	char** argl;
	int status;

	do {
		printf("%s%d", PROMPT, EXIT_FAILURE);

		// get line
		char* line = read_line();
		// parse line
		// execute line
		// set status

	} while(status != 0);

}

char* read_line(void) {
	short buff_len = LBUFF_LEN;
	int pos = 0;
	char* buff = (char *)malloc(buff_len * sizeof(char));

	char c;

	if(!buff) {
		printf("MSH: Line buffer allocation error\n");
		exit(1);
	}

	while(true) {
		c = getc(stdin);

		if(c == -1 || c == '\r' || c == '\n') {
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

	char** out = (char **)malloc(buff_len * sizeof(char *));
	char* token;

	if(!tokens) {
		printf("MSH: Token buffer allocation error\n");
		exit(1);
	}

	return NULL;
}

