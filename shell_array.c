#include <stdio.h>
#include <stdlib.h>

long *Array_Load_From_File(char *filename, int *size) {
    FILE *file = fopen(filename, "rb");

    if(file == NULL) {
        *size = 0;
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    *size = ftell(file) / sizeof(long);
    
    fseek(file, 0L, SEEK_SET);

    long *array = malloc((*size) * sizeof(*array));
    
    fread(array, sizeof(*array), *size, file);
    fclose(file);

    return (array);
}

int Array_Save_To_File(char *filename, long *array, int size) {
    //saves array to an external file called filename
    FILE* file  = fopen(filename, "wb");
    //if array is null or size is 0, create empty output file - TODO
    int success = fwrite(array, sizeof(*array), size, file);
    fclose(file);
    return success;
    //return the number of integers saved in array
}

void Array_Shellsort(long *array, int size, long *n_comp) {
    int gap = 1;
    (*n_comp) = 0;

    while(gap < size) gap = (gap * 3) + 1;

    gap = (gap - 1) / 3;

    while(gap > 0) {
        int iterator = gap;
        while(iterator < size) {
            long hold = array[iterator];
            long iter2 = iterator;
            while(iter2 >= gap && array[iter2 - gap] > hold) {
                array[iter2] = array[iter2 - gap];
                iter2 = iter2 - gap;
                *n_comp = *n_comp + 1;
            }
            array[iter2] = hold;
            *n_comp = *n_comp + 1;
            iterator++;
        }
        gap = (gap - 1) / 3;
    }
}