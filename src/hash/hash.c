#include "hash.h"

inline unsigned int oat_hashf(void *val, const int len) {
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