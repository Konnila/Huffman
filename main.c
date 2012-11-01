

#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include <limits.h>
#define TOPINDEX     1

typedef struct Node {
    char symbol;
    int frequency;
    int index;

} Node;

int heap_size = 0;
Node* heap[1000];



void heapify(Node* top);
Node* heap_del_min(Node* top);
void heap_insert(Node* top, int frequency, char symbol);

//todo free
Node* heap_del_min(Node* top) {
    Node* min = top;
    heap[TOPINDEX] = heap[heap_size];
    heap[TOPINDEX]->index = 1;
    heap_size--;
    
    
    heapify(heap[TOPINDEX]);

    return min;

}

void heap_insert(Node* top, int frequency, char symbol) {

    Node* add = malloc(sizeof (Node));
    add->frequency = frequency;
    add->symbol = symbol;
    add->index = 1;

    if (heap_size == 0) {
        heap[1] = add;
        heap_size++;
        return;
    }
    //indexes start from 1 because of the next while-loop
    int ind = heap_size + 1;
    add->index = ind;
    heap_size++;

    //upheaval
    while (ind > 1 && add->frequency < heap[(add->index) / 2]->frequency) {
        heap[ind / 2]->index = ind;
        heap[ind] = heap[ind / 2];
        ind = ind / 2;
        add->index = ind;
    }
    heap[ind] = add;

}

void heapify(Node* top) {
    Node* min = top;

    Node* left = heap[top->index * 2];
    Node* right = heap[top->index * 2 + 1];

    //no children
    if (right == NULL && left == NULL) return;
    //both children
    if (right != NULL) {
        if (left->frequency < right->frequency) {
            min = left;
        } else min = right;
        if (top->frequency > min->frequency) {
            int topInd = top->index;
            top->index = min->index;
            heap[min->index] = top;
            min->index = topInd;
            heap[topInd] = min;
            heapify(min);
        }
        //only left child
    } else if (left != NULL && top->frequency > left->frequency) {
        int topInd = top->index;
        top->index = left->index;
        heap[left->index] = top;
        left->index = topInd;
        heap[topInd] = left;
    }

}

int main(int argc, char** argv) {
    heap_insert(heap[0], 5, 'c');
    heap_insert(heap[0], 65, 'a');
    heap_insert(heap[0], 30, 'b');
    heap_insert(heap[0], 7, 'F');
    heap_insert(heap[0], 666, 'h');
    heap_insert(heap[0], 2, 'g');
    // g, c, F, b, a, h

    printf("at index: %d IS symbol: %c\n", heap[1]->index, heap[1]->symbol);
    printf("at index: %d IS symbol: %c\n", heap[2]->index, heap[2]->symbol);
    printf("at index: %d IS symbol: %c\n", heap[3]->index, heap[3]->symbol);
    printf("at index: %d IS symbol: %c\n", heap[4]->index, heap[4]->symbol);
    printf("at index: %d IS symbol: %c\n", heap[5]->index, heap[5]->symbol);
    printf("at index: %d IS symbol: %c\n", heap[6]->index, heap[6]->symbol);

    Node* deleted = heap_del_min(heap[1]);
    printf("Just deleted %c from the heap\n", deleted->symbol);
    puts("AFTER DELETION TREE IS AS FOLLOWS\n");
    printf("at index: %d IS symbol: %c\n", heap[1]->index, heap[1]->symbol);
    printf("at index: %d IS symbol: %c\n", heap[2]->index, heap[2]->symbol);
    printf("at index: %d IS symbol: %c\n", heap[3]->index, heap[3]->symbol);
    printf("at index: %d IS symbol: %c\n", heap[4]->index, heap[4]->symbol);
    printf("at index: %d IS symbol: %c\n", heap[5]->index, heap[5]->symbol);



    FILE* fptr = fopen("testfile.txt", "r");




    return (EXIT_SUCCESS);
}

