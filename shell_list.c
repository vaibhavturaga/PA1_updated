#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shell_list.h"
#include "list_of_list.h"
//for testing only - REMOVE LATER
void print_list(Node* head) {
    Node *current = head;

    while(current != NULL) {
        printf("%ld, ", current->value);
        current = current->next;
    }
    printf("\n");
}

Node *List_Load_From_File(char *filename) {
    FILE* file = fopen(filename, "rb");

    fseek(file, 0L, SEEK_END);
    int size = ftell(file) / sizeof(long);
    fseek(file, 0L, SEEK_SET);

    Node* head = NULL;
    Node* current = head;

    for(int i = 0; i < size; i++) {
        Node* temp = malloc(sizeof(*temp));
        fread(&(temp->value), sizeof(long), 1, file);
        temp->next = NULL;
        if(head == NULL) {
            head = temp;
            current = head;
        }
        else {
            current->next = temp;
            current = current->next;
        }
    }
    fclose(file);
    return head;
}

int List_Save_To_File(char *filename, Node *list) {
    int success = 0;
    //saves array to an external file called filename
    FILE* file  = fopen(filename, "wb");
    //if array is null or size is 0, create empty output file
    while(list != NULL) {
        fwrite(&(list->value), sizeof(list->value), 1, file);
        list = list->next;
        success = success + 1;
    }
    fclose(file);
    return success;
}

static void _swap_nodes(Node* prev, Node* curr) {
    if(prev->next == curr) {
        prev->next = curr->next;
        curr->next = curr->next->next;
        prev->next->next = curr;
    }
    else {
        Node* temp = prev->next->next;
        prev->next->next = curr->next->next;
        curr->next->next = temp;
        temp = prev->next;
        prev->next = curr->next;
        curr->next = temp;
    }
}

Node *List_Shellsort(Node *list, long *n_comp) {
    int num_elements = 0;
    Node* iterator = list;
    while(iterator != NULL) {
        iterator = iterator->next;
        num_elements++;
    }
    printf("Num elements: %ld\n", num_elements);
    int gap = 0;
    *n_comp = 0;
    
    while(gap < num_elements) gap = (gap * 3) + 1;
    gap = (gap - 1) / 3;

    Node* head = (Node*) malloc(sizeof(*head));
    head->value = 1;
    head->next = list;

    while(gap > 0) {
        for(int i = 0; i < num_elements; i++){
            Node* prev = head;
            Node* curr = prev;
            for(int k = 0; k < gap; k++){
                curr = curr->next;
            }

            for(int j = gap; j < num_elements - i * gap; j++){
                if(curr->next->value < prev->next->value) {
                    _swap_nodes(prev, curr);
                }
                *n_comp += 1;

                prev = prev->next;
                if (gap != 1){
                    curr = curr->next;
                }
                else{
                    curr = prev->next;
                }
            }
        }
        gap = (gap - 1) / 3;
    }

    list = head->next;
    free(head);
    return list;

}

