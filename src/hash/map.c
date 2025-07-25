#include "hash.h"

sspair* get_ssp(ssmap* mp, const char* _key) {
    unsigned int idx = oat_hashf(_key, strlen((char *)_key)) % mp->cap;

    struct sspair* temp = mp->data[idx];
    if(!temp)
        return NULL;

    while(temp) {
        if(strcmp(temp->key, _key) == 0) {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}
const char* get_ssval(ssmap* mp, const char* _key) {
    return get_ssp(mp, _key)->val;
}

bool ssminsert(ssmap* mp, sspair ssp) {
    struct sspair* in_pair = (sspair *)malloc(sizeof(sspair));
    in_pair->key = strdup(ssp.key); // replace w/ strdup
    in_pair->val = strdup(ssp.val); // replace w/ strdup

	/*
    in_pair->key = (char *)malloc(strlen(ssp.key) + 1); // replace w/ strdup
    in_pair->val = (char *)malloc(strlen(ssp.val) + 1); // replace w/ strdup
    in_pair->next = NULL;

    if(!(in_pair && in_pair->key && in_pair->val)) {
        MSHERR("Allocation error")
        return false;
    }

    strcpy(in_pair->key, ssp.key);
    strcpy(in_pair->val, ssp.val);
	*/

    if(!ssminsertp(mp, in_pair)) {
        free(in_pair);
        return false;
    }

    return true;
}
bool ssminsertss(ssmap* mp, const char* _key, const char* _val) {
    if(!_key)
        return false;

    struct sspair* in_pair = (sspair *)malloc(sizeof(sspair));
    if(!in_pair) {
        MSHERR("Allocation error")
        return false;
    }

    in_pair->key = _key;
    in_pair->val = _val;
    in_pair->next = NULL;

    if(!ssminsertp(mp, in_pair)) {
        free(in_pair);
        return false;
    }

    return true;
}
bool ssminsertp(ssmap* mp, sspair* ssp) {
    if(!ssp)
        return false;
    if(mp->size >= mp->cap) {
        return false;
    }

    unsigned int idx = oat_hashf(ssp->key, strlen(ssp->key)) % mp->cap;

    struct sspair* bucket = mp->data[idx];
    if(!bucket) {
        mp->data[idx] = ssp;
    } else {
        while(bucket->next) {
            if(strcmp(bucket->key, ssp->key) == 0)
                return false;

            bucket = bucket->next;
        }

        bucket->next = ssp;
    }

    mp->size++;
    if(mp->size * 4 >= mp->cap * 3) {
        if(mp->cap <= INF / 2) {
            mp->cap *= 2;

            if(!ssrehash(mp, mp->cap / 2, NULL)) {
                mp->cap /= 2;
                MSHERR("Critical rehashing error")
                return false;
            }
        }
    }

    return true;
}

bool ssmremove(ssmap* mp, const char* _key) {
    if(!_key)
        return false;

    unsigned int idx = oat_hashf(_key, strlen(_key)) % mp->cap;

    sspair* curr = mp->data[idx];
    if(!curr)
        return false;

    if(strcmp(curr->key, _key) == 0) {
        mp->data[idx] = curr->next;
        free(curr);

        mp->size--;
        return true;
    }

    while(curr->next) {
        if(strcmp(curr->next->key, _key) == 0) {
            sspair* temp = curr->next;
            curr->next = curr->next->next;
            free(temp);

            mp->size--;
            return true;
        }
    }

    return false;
}

bool ssrehash(ssmap* mp, const unsigned int old_len, unsigned int (*hash_func) (const void *, int)) {
    if(!hash_func) {
        hash_func = oat_hashf;
    }

    struct sspair** old_data = mp->data;
    
    mp->data = (sspair **)calloc(sizeof(sspair *), mp->cap);
    mp->size = 0;
    
    sspair* item;
    for(unsigned int i = 0; i < old_len; i++) {
        item = old_data[i];

        while(item) { // go through original bucket
            unsigned int idx = hash_func(item->key, strlen(item->key)) % mp->cap;

            sspair* bucket = mp->data[idx]; // find new bucket of item
            if(!bucket) {
                mp->data[idx] = item;

                struct sspair* temp = item->next;
                item->next = NULL;
                item = temp;

                continue;
            }
            
            while(bucket->next) { // go through new bucket to find open space
                bucket = bucket->next;
            }
            bucket->next = item;

            struct sspair* temp = item->next;
            item->next = NULL;
            item = temp;
        }
    }

    free(old_data);
    return true;
}

void print_ssmp(ssmap* mp) {
    for(int i = 0; i < mp->cap; i++) {
		if(mp->data[i]) {
			struct sspair* bucket = mp->data[i];

			unsigned count = 0;
			while(bucket) {
				printf("[%d:%d] Key: %s, Val: %s\n", i, count++, bucket->key, bucket->val);
				bucket = bucket->next;
			}
		}
		// else
		// 	printf("[%d] Key: NULL, Val: NULL\n", i);
	}
	printf("\n\n");
}
