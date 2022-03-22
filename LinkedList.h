#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#define FALSE 0

typedef struct LinkedListNode {
    struct LinkedListNode* next;
    void* data;

} LinkedListNode;

typedef struct LinkedList {
    int count;
    LinkedListNode* head;
    LinkedListNode* tail;

} LinkedList;

/*function pointers for printing different datatype in data of nodes*/
typedef void (*listFunc) (void* data);

LinkedList* createLinkedList();
LinkedListNode* createLinkedListNode();
void insertStart(LinkedList* list, void* entry);
void* removeStart(LinkedList* list);
void insertLast(LinkedList* list, void* entry);
void* removeLast(LinkedList* list);
void printLinkedList(LinkedList* list, listFunc printFunction);
void freeLinkedList(LinkedList* list, listFunc freeFunction);

/*not mentioned on worsheet*/
LinkedListNode* findSecondLast(LinkedList* list);
void increasecountByOne(LinkedList* list);
void decreasecountByOne(LinkedList* list);
void printString(void* string);
void printInt(void* integer);
void freeString(void* string);
#endif