typedef struct dictionary dictionary;

/* dict_create( ) = an empty dictionary */
dictionary* dict_create(void);

/* dict_add(d, k, v) : adds key-value pair (k, v) to dictionary d. If k is in d, replace its value with v */
void dict_add(dictionary*, char, int);

/* dict_size(d) = the size of the dictionary d */
int dict_size(dictionary*);

/* dict_return_all_keys(d) = an array of all the keys in the dictionary d */
char* dict_return_all_keys(dictionary*);

/* dict_key_in_dictionary(d, k) = true, if key k is in dictionary d
*                                 false, if otherwise */
bool dict_key_in_dictionary(dictionary*, char);

/* dict_keys_value(d, k) = the value associated with key k in dictionary d 
* Pre-condition: key k is in dictionary d */
int dict_keys_value(dictionary*, char);

/* dict_delete(d, k) : deletes key-value pair (k, value) from the dictionary d 
* Pre-condition: key k is in dictionary d */
void dict_delete(dictionary*, char);

/* dict_free(d) : frees all memory associated with the dictionary d. Frees all nodes at all indexes in the hash table, and frees the dictionary d */
void dict_free(dictionary*);

/* dict_print(d) : prints all of the key-value pairs in dictionary d */
void dict_print(dictionary*);