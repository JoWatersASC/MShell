#ifndef JW_HASH_H
#define JW_HASH_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "shell.h"

#define INF 0x3F3F3F3F

extern inline unsigned int oat_hashf(void *val, const int len);

// Hashmap specifications
typedef struct sspair { // string-string pair
    const char* key;
    char* val;
    struct sspair* next;
} sspair;

typedef struct ssmap { // string-string map
    struct sspair** data;
    unsigned int size;
    unsigned int cap;
} ssmap;

extern inline ssmap* make_ssmap(unsigned int _cap);
extern inline void print_ssmp(ssmap *);

sspair* get_ssp(ssmap *, const char *);
char* get_ssval(ssmap *, const char *);

bool ssminsert(ssmap *, sspair);
bool ssminsertss(ssmap *, char *, char *);
bool ssminsertp(ssmap *, sspair *);

bool ssmremove(ssmap *, char *);

bool ssrehash(ssmap*, unsigned int, unsigned int (*) (void *, int));

#endif