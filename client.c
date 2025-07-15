#include <stdio.h>
#include <stdbool.h>
#include "dictionary.h"

int main(void){

    printf("Creating a dictionary...\n");
    dictionary* d = dict_create();

    printf("\nOpening the test.txt file...\n");
    FILE* file;
    file = fopen("test.txt","r");

    printf("\nLooping through each character in the file and adding it to the dictionary or incrementing the integer value...\n");
    char c;
    while((c = fgetc(file)) != EOF) {
        if (dict_key_in_dictionary(d, c) == false){
            dict_add(d, c, 1);
        } else{
            int current_value = dict_keys_value(d, c);
            /*I'm using dict_add because this function will change c's integer value in the dictionary (because c is already in the dictionary)*/
            dict_add(d, c, (current_value+1));
        }
    }
    fclose(file);

    printf("\nPrinting the dictionary...\n");
    dict_print(d);

    printf("\nDeleting all values in the dictionary...\n");
    char* all_keys_array = dict_return_all_keys(d);
    int original_dict_size = dict_size(d);
    for (int i = 0; i < original_dict_size; i++){
        dict_delete(d, all_keys_array[i]);
    }

    printf("\nPrinting the dictionary again (to verify that it is empty)...\n");
    dict_print(d);

    printf("\nOpening the occurrence.txt file...\n");
    FILE* file1;
    file1 = fopen("occurrence.txt","r");

    printf("\nLooping through each character in the file and adding it to the dictionary or incrementing the integer value...\n");
    char c1;
    while((c1 = fgetc(file1)) != EOF) {
        if (dict_key_in_dictionary(d, c1) == false){
            dict_add(d, c1, 1);
        } else{
            int current_value = dict_keys_value(d, c1);
            /*I'm using dict_add because this function will change c's integer value in the dictionary (because c is already in the dictionary)*/
            dict_add(d, c1, (current_value+1));
        }
    }
    fclose(file1);

    printf("\nPrinting the dictionary...\n");
    dict_print(d);

    printf("\nFreeing the memory associated with the dictionary...\n\n");
    dict_free(d);

    printf("Done!");

    return 0;
}