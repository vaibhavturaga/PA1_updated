#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shell_array.h"
#include "shell_list.h"
#include "string.h"
int main(int argc, char* argv[]) {
    //
    if(argc != 4) {
        return -1;
    }

    
    char* filename = argv[2];

    //array load from file
    if(strcmp(argv[1], "-a") == 0){
        int size;
        long* array = Array_Load_From_File(filename, &size);
        long n_comp = 0;
        //run shellsort and save to file  
        Array_Shellsort(array, size, &n_comp);
        Array_Save_To_File(argv[3], array, size);    
        
        //free array memory and print number of comparisons
        free(array);
        printf("%ld\n", n_comp);
    }  
    else if(strcmp(argv[1],"-l") == 0) {
        long n_comp = 0;
        //load, sort and save list
        printf("Loading list\n");
        Node* list = List_Load_From_File(argv[2]);
        if(list == NULL) {
            return EXIT_FAILURE;
        }
        printf("Sorting List\n");
        list = List_Shellsort(list, &n_comp);
        printf("Saving sorted list\n");
        List_Save_To_File(argv[3], list);

        //print comparisons
        printf("%ld\n", n_comp);

        //free list
        Node* curr;
        while(list != NULL) {
            curr = list;
            list = list->next;
            free(curr);
        }
    }  

}