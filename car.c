#include <stdio.h>
#include <stdlib.h>
typedef struct Node{
    int d;
    struct Node* next;
} Node;

Node* createNode(int data)
{
    Node* ptr= (Node*)malloc(sizeof(Node));
    ptr->d=data;
    ptr->next=NULL;
    return ptr;
}

Node* createList(int size) {
    Node* head = NULL;
    Node* tail = NULL;
    int entry;

    printf("Enter data: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &entry);
        Node* nptr = createNode(entry);

        if (head == NULL) {
            head = nptr;
            tail = nptr;
        } else {
            tail->next = nptr;
            tail = nptr;
        }
    }
    tail->next = head; 
    return tail;       
}
