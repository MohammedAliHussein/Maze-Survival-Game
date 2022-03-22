/*  FILE: LinkedList.c
 *  AUTHOR: Mohammed-Ali Hussein 
 *  STUDENT ID: 20184133
 *  UNIT: COMP 1000 
 *  PURPOSE: Allow for use of linked list abstract data type
 *  LAST MOD: 22/09/21
 *  REQUIRES: fileIO.h freeMemory.h */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


/*  NAME: createLinkedList
 *  PURPOSE: Initalise linked list data type
 *  IMPORTS: none
 *  EXPORTS: list (address of the linked list)
 *  ASSERTIONS: 
 *       PRE: none
 *       POST: linked list is initialised  */
LinkedList* createLinkedList()
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}


/*  NAME: createLinkedListNode
 *  PURPOSE: Initalise linked list node data type
 *  IMPORTS: none
 *  EXPORTS: node (address of the list node)
 *  ASSERTIONS: 
 *       PRE: none
 *       POST: list node is initialised  */
LinkedListNode* createLinkedListNode()
{
    LinkedListNode* node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->data = NULL;
    return node;
}


/*  NAME: printLinkedList
 *  PURPOSE: print contents of linked list
 *  IMPORTS: list(address of the linked list),
    printFunction(address of the function to print the data type
    in the nodes)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: linked list is initialised with data
 *       POST: list contents are printed  */
/* make function pointer for printing all datatypes. */
void printLinkedList(LinkedList* list, listFunc printFunction)
{
    LinkedListNode* node = list->head;
    int done = 0;

    while(!done)
    {
        if(node == NULL)
        {
            done = 1;
        }
        else
        {
            printFunction(node->data);
            node = node->next;
        }
    }        
}


/*  NAME: freeLinkedList
 *  PURPOSE: de-allocate memory of the linked list
 *  IMPORTS: list(address of the linked list),
    freeFunction(address of the function to free the data type in the nodes)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: linked list is initialised with data
 *       POST: list is freed  */
/* make function pointer for freeing all types i.e. string, 2d array, struct etc. */
void freeLinkedList(LinkedList* list, listFunc freeFunction)
{
    if(!(list->head == NULL && list->tail == NULL))
    {
        /*first free the contents of the data*/
        LinkedListNode* currentNode = list->head;
        LinkedListNode* nextNode;

        while(currentNode != NULL)
        {
            freeFunction(currentNode->data);
            currentNode = currentNode->next;
        }

        /*second free the nodes*/
        currentNode = list->head;
        nextNode = currentNode->next;

        while(nextNode != NULL)
        {
            free(currentNode);
            currentNode = nextNode;
            nextNode = currentNode->next;
        }

        /*when you get to the end, nextNode will be null and there will be 1 unFreed node left
        so free that last node outside the loop*/
        free(currentNode);

        /*free the list itself*/
        free(list);
    }
}


/*  NAME: insertStart
 *  PURPOSE: add node to start of linked list
 *  IMPORTS: list(address of the linked list),
    entry(address of the data to be added at the start)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: linked list is initialised
 *       POST: entry is added to the start of the list */
void insertStart(LinkedList* list, void* entry)
{
    if(list->head == NULL && list->tail == NULL)
    {
        list->head = createLinkedListNode();
        list->head->data = entry;
        list->tail = list->head;
        increasecountByOne(list);
    }
    else if(list->count == 1)
    {
        LinkedListNode* newNode = createLinkedListNode();
        newNode->data = entry;
        list->head = newNode;
        list->head->next = list->tail;
        increasecountByOne(list);
    }
    else
    {
        LinkedListNode* newNode = createLinkedListNode();
        newNode->data = entry;
        newNode->next = list->head;
        list->head = newNode;
        increasecountByOne(list);
    }
}


/*  NAME: removeStart
 *  PURPOSE: remove the start node of the list
 *  IMPORTS: list(address of the linked list),
 *  EXPORTS: pointer(address of the data in the removed node)
 *  ASSERTIONS: 
 *       PRE: linked list is initialised with atleast 1 node
 *       POST: first node's data is returned */
void* removeStart(LinkedList* list)
{
    void* pointer = NULL;

    if(!(list->head == NULL))
    {
        pointer = list->head->data;
        list->head = list->head->next;
        decreasecountByOne(list);
    }

    return pointer;
}


/*  NAME: insertLast
 *  PURPOSE: add a node to the end of a linked list
 *  IMPORTS: list(address of the linked list),
    entry(address of data to be added to the end of the list)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: linked list is initialised
 *       POST: entry is added to the end of the list */
void insertLast(LinkedList* list, void* entry)
{
    if(list->head == NULL && list->tail == NULL)
    {
        list->head = createLinkedListNode();
        list->head->data = entry;
        list->tail = list->head;
        increasecountByOne(list);
    }
    else if(list->count == 1)
    {
        LinkedListNode* newNode = createLinkedListNode();
        newNode->data = entry;
        list->head->next = newNode;
        list->tail = list->head->next;
        increasecountByOne(list);
    }
    else
    {
        LinkedListNode* newNode = createLinkedListNode();
        newNode->data = entry;
        list->tail->next = newNode;
        list->tail = list->tail->next;
        increasecountByOne(list);
    }
}


/*  NAME: removeLast
 *  PURPOSE: remove the last node of the list
 *  IMPORTS: list(address of the linked list),
 *  EXPORTS: pointer(address of the data in the removed node)
 *  ASSERTIONS: 
 *       PRE: linked list is initialised with atleast 1 node
 *       POST: last node's data is returned */
void* removeLast(LinkedList* list)
{
    void* pointer = NULL;

    /*if(!(list->head == NULL && list->tail == NULL))*/
    if(list->count >= 1)
    {
        pointer = list->tail->data;
        free(list->tail);

        if(list->count == 1)
        {
            /*since both head and tail are the same
            i.e. only 1 entry, delete both*/
            list->tail = NULL;
            list->head = NULL;
            decreasecountByOne(list);        
        }
        else
        {
            list->tail = findSecondLast(list);
            list->tail->next = NULL;
            decreasecountByOne(list); 
        }
    }

    return pointer;
}


/*  NAME: findSecondLast
 *  PURPOSE: locate the second last node in the linked list
 *  IMPORTS: list(address of the linked list)
 *  EXPORTS: currentNode(address of the second last node)
 *  ASSERTIONS: 
 *       PRE: linked list is initialised 
 *       POST: second last node's address is returned */
LinkedListNode* findSecondLast(LinkedList* list)
{
    int found = 0;
    LinkedListNode* currentNode = list->head;

    while(!found)
    {
        if(currentNode->next == list->tail)
        {
            found = 1;
            
        }
        else
        {
            currentNode = currentNode->next;
        }
    }

    return currentNode;
}


/*  NAME: increasecountByOne
 *  PURPOSE: increase the count of the linked list by 1
 *  IMPORTS: list(address of the linked list)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: linked list is initialised 
 *       POST: list's count incremented by 1 */
void increasecountByOne(LinkedList* list)
{
    list->count = list->count + 1;
}


/*  NAME: decreasecountByOne
 *  PURPOSE: decrease the count of the linked list by 1
 *  IMPORTS: list(address of the linked list)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: linked list is initialised 
 *       POST: list's count decreased by 1 */
void decreasecountByOne(LinkedList* list)
{
    list->count = list->count - 1;
}


/*  NAME: freeString
 *  PURPOSE: de-allocate memory of string
 *  IMPORTS: string(address of string)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: string is dynamically allocated as void*
 *       POST: string's memeory is de-allcoated */
void freeString(void* string)
{
    free(string);
}


/*  NAME: printString
 *  PURPOSE: print string
 *  IMPORTS: string(address of string)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: string is dynamically allocated as void*
 *       POST: string is printed */
void printString(void* string)
{
    printf("%s\n", (char*)string);
}