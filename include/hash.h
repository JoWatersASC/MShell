#ifndef JW_HASH_H
#define JW_HASH_H

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "shell.h"

#define INF 0x3F3F3F3F


// Hashmap specifications
typedef struct sspair { // string-string pair
    const char* key;
    const char* val;
    struct sspair* next;
} sspair;

typedef struct ssmap { // string-string map
    struct sspair** data;
    unsigned int size;
    unsigned int cap;
} ssmap;


sspair* get_ssp(ssmap *, const char *);
const char* get_ssval(ssmap *, const char *);

bool ssminsert(ssmap *, sspair);
bool ssminsertss(ssmap *, const char *, const char *);
bool ssminsertp(ssmap *, sspair *);

bool ssmremove(ssmap *, const char *);
bool ssrehash(ssmap*, unsigned int, unsigned int (*) (const void *, int));

void print_ssmp(ssmap *);

static inline unsigned int oat_hashf(const void *val, const int len) {
    unsigned char *p = (unsigned char *)val;
    unsigned int hash = 0;
    int i;

    for ( i = 0; i < len; i++ ) {
        hash += p[i];
        hash += ( hash << 10 );
        hash ^= ( hash >> 6 );
    }
 
    hash += ( hash << 3 );
    hash ^= ( hash >> 11 );
    hash += ( hash << 15 );

    return hash;
}
inline ssmap* make_ssmap(unsigned int _cap) {
    struct ssmap* out = (ssmap *)malloc(sizeof(ssmap));

    out->data = (sspair **)calloc(sizeof(sspair *), _cap);
    out->size = 0;
    out->cap = _cap;

    return out;
}
#endif
