#include <hash_table.h>
#include <linked_list.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/* From http://www.cse.yorku.ca/~oz/hash.html */
int hash_fun (const char* word, size_t n) {
    unsigned int hash = 0;
    for (int i = 0 ; word[i] != '\0' ; i++)
    {
        hash = 31*hash + word[i];
    }
    return hash % n;
}

/* n: number of elements */
node_t** hash_table_init(size_t n) {
    node_t** table = calloc(2 * n, sizeof(node_t*));
    return table;
}

/* n is the size of the hash table */
int hash_table_insert_string_nodup(node_t** table, size_t n, char* str) {
    /* Compute hash */
    unsigned long hash = hash_fun(str, n);

    /* Select list from table */
    node_t* curr = table[hash];

    while(curr != NULL) {
        /* Do not insert a duplicate! */
        if(strcmp(str, (char*)curr->val) == 0) {
            errno = ECANCELED;
            return -1;
        }
        curr = curr->next;
    }

    /* No duplicate found, copy string and insert */
    char* tmp = malloc(strlen(str) + 1);
    strcpy(tmp, str);
    table[hash] = list_insert_head(table[hash], (void*) tmp);
    return 0;
}
