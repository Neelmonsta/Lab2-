#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define ht_size 0x1000000

static const int ht_get_h(const char * key, const size_t key_len) {
	int hash = 0;
	size_t i = key_len;
	while (i > 0) {
		--i;
		hash += key[i] << (8 * i % 24);
	}
	
	return hash % ht_size;
}

struct _ht_item {
	struct _ht_item * last, * next; 
	const char * key;
	size_t key_len;
	const void * value; 
};
typedef struct _ht_item ht_item;
 
static  void ht_item_set(ht_item ** ht, const char * key, const void * value) {
	const size_t key_len = strlen(key);
	const int index = ht_get_h(key, key_len);
	ht_item ** ht_i = &ht[index], *last = NULL;
	while (true) {
		if (*ht_i == NULL) {
			ht_item  * hi = malloc(sizeof(ht_item));
			hi->last = last;
			hi->next = NULL;
			hi->key = key;
			hi->key_len = key;
			hi->value = value;
			*ht_i = hi;
			return;
		}
		else if ((*ht_i)->key_len == key_len && memcmp((*ht_i)->key, key, key_len) == 0) {
			(*ht_i)->value = value;
			return;
		}
		last = *ht_i;
		ht_i = &(*ht_i)->next;
	}
}
static const void* ht_item_get(ht_item** ht, const char* key) {
	const size_t key_len = strlen(key);
	const int index = ht_get_h(key, key_len);
	ht_item** ht_i = &ht[index];
	while (true) {
		if (*ht_i != NULL) {
			if ((*ht_i)->key_len == key_len && memcmp((*ht_i)->key, key, key_len == 0))
				return(*ht_i)->value;
		}
		else
			return NULL;
		ht_i = &(*ht_i)->next;
	}
}
//static const void * ht_item_get(ht_item ** ht, const char * key) {
	//const size_t key_len = strlen(key);
//	const int index = ht_get_h(key, key_len);
	//ht_item ** ht_i = &ht[index];
	//while (true) {
		//if (*ht_i != NULL) {
			//if ((*ht_i)->key_len == key_len && memcmp((*ht_i)->key, key, key_len) == 0) {
				//return (*ht_i)->value;
			//}
		//}
		//else
			//return NULL;
		//ht_i = &(*ht_i)->next;
	//}
//}

static const bool  ht_item_del(ht_item ** ht, const  char* key) {
	const size_t key_len = strlen(key);
	const int index = ht_get_h(key, key_len);
	ht_item ** ht_i = &ht[index];
	while (true) {
		if (*ht_i != NULL) {
			if ((*ht_i)->key_len == key_len && memcmp((*ht_i)->key, key, key_len == 0)) {
				ht_item* ht_i_n = (*ht_i)->next;
				free(*ht_i);
				*ht_i = ht_i_n;
				return true;
			}
		}
		else
			return false;
		ht_i = &(*ht_i)->next;
	}
}
static const bool ht_item_serch(ht_item** ht, const  char* key) {
	const size_t key_len = strlen(key);
	const int index = ht_get_h(key, key_len);
	ht_item** ht_i = &ht[index];
	while (true) {
		if (*ht_i != NULL) {
			if ((*ht_i)->key_len == key_len && memcmp((*ht_i)->key, key, key_len == 0))
				return true;
		}
		else
			return false;
		ht_i = &(*ht_i)->next;
	}
}





int main() {
	ht_item ** ht = calloc(ht_size, sizeof(ht_item*));
	ht_item_set(ht, "first",  (void*)12345);
	ht_item_set(ht, "second", (void*)"this is test");
 	printf("%d\n", ht[7527897]->value);
	

}