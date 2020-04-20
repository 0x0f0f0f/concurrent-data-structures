#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <linked_list.h>

/* From http://www.cse.yorku.ca/~oz/hash.html */
unsigned long hash_char_djb2(unsigned char *str);

/* n: number of elements */
node_t** hash_table_init(size_t n);

/* n is the size of the hash table */
int hash_table_insert_string_nodup(node_t** table, size_t n, char* str);
#endif
