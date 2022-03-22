/*  FILE: main.c
 *  AUTHOR: Mohammed-Ali Hussein 
 *  STUDENT ID: 20184133
 *  UNIT: COMP 1000 
 *  PURPOSE: Entry point for main game processes
 *  LAST MOD: 23/08/21
 *  REFERENCE: Submitted for assignment 1 COMP 1000 2021 semester 2 
 *  REQUIRES: mazeSetup.h freeMemory.h fileIO.h*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mazeSetup.h"
#include "freeMemory.h"
#include "fileIO.h"


int main(int argc, char* argv[])
{
    int** tableData = NULL;
    int metaDataAmount, mapRow, mapColumn, successfulRead;

    if(argc < 2 || argc > 2)
    {
        /*if the user does not enter a possible filename*/
        printf("You must enter a single filename(X). [./maze X]\n");
    }
    else
    {
        successfulRead = getMetadata(&tableData, &metaDataAmount, &mapRow, &mapColumn, argv[1]);
        if(successfulRead)
        {
            setupMaze(mapRow, mapColumn, &tableData, metaDataAmount);
            free2dIntArray(metaDataAmount, &tableData);             
        }
    }

    return 0;
}