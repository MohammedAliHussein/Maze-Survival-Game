/*  FILE: freeMemory.c
 *  AUTHOR: Mohammed-Ali Hussein 
 *  STUDENT ID: 20184133
 *  UNIT: COMP 1000 
 *  PURPOSE: De-allocate memory for 2d int 
 *  and char arrays
 *  LAST MOD: 23/08/21
*  REFERENCE: Submitted for assignment 1 COMP 1000 2021 semester 2 
 *  REQUIRES: freeMemory.h mazeEntityStates.h*/


#include <stdio.h>
#include <stdlib.h>
#include "freeMemory.h"
#include "mazeEntityStates.h"


/*  NAME: free2dCharArray
 *  PURPOSE: De-allocated heap memory of 2d char array
 *  IMPORTS:  r(number of rows), array(address of the
    array to be de-allocated)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: array has been allocated
 *       POST: array has been de-allocated */
void free2dCharArray(int r, char*** array)
{
    char** rows = *array;

    int i;
    for(i=0; i<r; i++)
    {
        free(rows[i]);
    }

    free(rows);
}


/*  NAME: free2dIntArray
 *  PURPOSE: De-allocated heap memory of 2d int array
 *  IMPORTS:  r(number of rows), array(address of the
    array to be de-allocated)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: array has been allocated
 *       POST: array has been de-allocated */
void free2dIntArray(int r, int*** array)
{
    int** rows = *array;

    int i;
    for(i=0; i<r; i++)
    {
        free(rows[i]);
    }

    free(rows);
}


/*  NAME: freeEntityStateArrays
 *  PURPOSE: De-allocated heap memory of a mazeEntitiesState struct
 *  IMPORTS:  data(address of the
    mazeEntitiesState struct to be de-allocated)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: mazeEntitiesState struct has been allocated
 *       POST: mazeEntitiesState struct has been de-allocated */
void freeEntityStateArrays(void* data)
{
    mazeEntitiesState* states = (mazeEntitiesState*)data;

    free(states->playerEntityState);
    free(states->snakeEntityState);
    free(data);
}