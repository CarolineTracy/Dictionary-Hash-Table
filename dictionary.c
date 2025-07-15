/* Note: I was running into errors and found that there were some characters in the .txt files that were causing a problem for me and not printing. I did some 
* research (and linked my sources above) and found that there is such a thing as unprintable characters, which is what these problem characters are. The sources I
* found said that there's a function in the ctype.h library called isprint, which checks if a character is printable or not. So, to combat my problem, I included 
* the library ctype.h in this file and used the isprint function to check if a character is printable or not. If the character is printable, I would continue with
* the function as normal (for example, I would add that character to the dictionary). However, if the character is not printable, I would not continue with the 
* function as normal and instead store that character as its ASCII code (for example, I would add that character's ASCII code to the dictionary). This way, I'm 
* able to avoid these unprintable characters and can make sure my functions can work as they're supposed to. However, this means that the \n character will not
* be included in my dictionary, since it's an unprintable character. */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"
#define TABLE_CAPACITY 25

typedef struct node {
    char key;
    int value;
    struct node* next;
} node;

typedef struct dictionary {
    struct node* hash_table[TABLE_CAPACITY];
    int size;
} dictionary;

/* hash(c) = c's index in the hash table (also known as the ASCII code of c % the hash table's capacity) */
unsigned int hash(char c){
    unsigned int result = (unsigned int)c % TABLE_CAPACITY;
    return result;
}

/* dict_create( ) = an empty dictionary */
dictionary* dict_create(void){
    dictionary* empty_dict = malloc(sizeof(dictionary));
    empty_dict->size = 0;
    return empty_dict;
}

/* dict_add(d, k, v) : adds key-value pair (k, v) to dictionary d. If k is in d, replace its value with v */
void dict_add(dictionary* d, char k, int v){
    int k_index = hash(k);
    /*Head of the linked list at the index k_index in the hash table:*/
    node* p = d->hash_table[k_index];
    if (isprint(k) != 0){
        if (dict_key_in_dictionary(d, k) == true){
            while (p != NULL){
                if (p->key == k){
                    p->value = v;
                    break;
                }
                p = p->next;
            }
        } else{
            node* inserted = malloc(sizeof(node));
            inserted->key = k;
            inserted->value = v;
            /*Adds (k, v) to the beginning of the sequence of nodes*/
            inserted->next = d->hash_table[k_index];
            d->hash_table[k_index] = inserted;
            d->size += 1;
        }
    }
}

/* dict_size(d) = the size of the dictionary d */
int dict_size(dictionary* d){
    return d->size;
}

/* dict_return_all_keys(d) = an array of all the keys in the dictionary d */
char* dict_return_all_keys(dictionary* d){
    int size_of_d = dict_size(d);
    char* all_keys_array = malloc(size_of_d * sizeof(char));
    int sizeof_all_keys_array = 0;
    for (int i = 0; i < TABLE_CAPACITY; i++){
        /*Run through all nodes in the node sequence at index i (in the dictionary d)*/
        node* p = d->hash_table[i];
        while (p != NULL){
            all_keys_array[sizeof_all_keys_array] = p->key;
            sizeof_all_keys_array += 1;
            p = p->next;
        }
    }
    return all_keys_array;
}

/* dict_key_in_dictionary(d, k) = true, if key k is in dictionary d
*                                 false, if otherwise */
bool dict_key_in_dictionary(dictionary* d, char k){
    bool k_in_d = false;
    char* all_keys_array = dict_return_all_keys(d);
    /*Run through all the chars in all_keys_array to see if they equal k*/
    for (int i = 0; i < dict_size(d); i++){
        if (all_keys_array[i] == k){
            k_in_d = true;
            break;
        }
    }
    /*Freeing all_keys_array because we used the function dict_return_all_keys, which manually allocates memory*/
    free(all_keys_array);
    return k_in_d;
}

/* dict_keys_value(d, k) = the value associated with key k in dictionary d 
* Pre-condition: key k is in dictionary d */
int dict_keys_value(dictionary* d, char k){
    int k_value;
    /*k_index is k's index in the hash table*/
    int k_index = hash(k);
    node* p = d->hash_table[k_index];
    while (p != NULL){
        if (p->key == k){
            k_value = p->value;
        }
        p = p->next;
    }
    return k_value;
}

/* dict_delete(d, k) : deletes key-value pair (k, value) from the dictionary d 
* Pre-condition: key k is in dictionary d */
void dict_delete(dictionary* d, char k){
    int k_index = hash(k);
    /*Head of the linked list at the index k_index in the hash table:*/
    node* p = d->hash_table[k_index];
    if (p->key == k){
        /*(If the head of the linked list's key is equal to k)*/
        node* temp = p;
        if (p->next != NULL){
            /*(If there is more than one node in this sequence of nodes)*/
            d->hash_table[k_index] = p->next;
        } else{
            /*(If there is only one node in this sequence of nodes)*/
            d->hash_table[k_index] = NULL;
        }
        free(temp);
    } else{
        /*(If the head of the linked list's key is not equal to k)*/
        while (p->next != NULL){
            /*Sees if the next node's key is equal to k*/
            if (p->next->key == k){
                node* temp = p->next;
                p->next = p->next->next;
                free(temp);
                break;
            }
            p = p->next;
        }
    }
    d->size -= 1;
}

/* free_nodes(p) : free all nodes reachable from p (including p) */
void free_nodes(node* p){
    node* temp = p;
    while(p != NULL) {
        temp = p;
        free(temp);
        p = p->next;
    }
}

/* dict_free(d) : frees all memory associated with the dictionary d. Frees all nodes at all indexes in the hash table, and frees the dictionary d */
void dict_free(dictionary* d){
    for(int i = 0; i < TABLE_CAPACITY; i++){
        node* p = d->hash_table[i];
        free_nodes(p);
    }
    free(d);
}

/* dict_print(d) : prints all of the key-value pairs in dictionary d */
void dict_print(dictionary* d){
    /*Running through all the nodes in all the indexes in the hash table*/
    for (int i = 0; i < TABLE_CAPACITY; i++){
        node* p = d->hash_table[i];
        while (p != NULL){
            printf("%c: %d\n", p->key, p->value);
            p = p->next;
        }
    }
    if (dict_size(d) == 0){
        printf("(Dictionary is empty)\n");
    }
}