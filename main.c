#include "shell.h"
#include "hash.h"

struct ssmap alias_map;
int main(void) {
	unsigned capacity = 8;

	alias_map.data = (sspair **)malloc(capacity * sizeof(sspair *));
	alias_map.size = 0;
	alias_map.cap = capacity;
	
	start_loop();
}
