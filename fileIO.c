/*  FILE: fileIO.c
 *  AUTHOR: Mohammed-Ali Hussein 
 *  STUDENT ID: 20184133
 *  UNIT: COMP 1000 
 *  PURPOSE: To process and read maze metadata from a file
 *  LAST MOD: 22/09/21
 *  REQUIRES: fileIO.h freeMemory.h */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileIO.h"
#include "freeMemory.h"


/*  NAME: getMetadata
 *  PURPOSE: Retreive metadata from a file
 *  IMPORTS: metadataTable(address which returned data will be stored),
    metadataAmount(number of objects in the file), mapRow(address where 
    number of rows will be stored), mapCol(address where number of columns
    will be stored), filename(address of the file to be read's name)
 *  EXPORTS: int (indicator of successful read)
 *  ASSERTIONS: 
 *       PRE: filename is atleast 1 character long
 *       POST: metadata is retrieved  */
int getMetadata(int *** metadataTable, int * metadataAmount, int * mapRow, int * mapCol, char* filename)
{
    return readFile(metadataTable, metadataAmount, mapRow, mapCol, filename);
}


/*  NAME: readFile
 *  PURPOSE: Read metadata from a file
 *  IMPORTS: metadataTable(address which returned data will be stored),
    metadataAmount(number of objects in the file), mapRow(address where 
    number of rows will be stored), mapCol(address where number of columns
    will be stored), filename(address of the file to be read's name)
 *  EXPORTS: int (indicator of successful read)
 *  ASSERTIONS: 
 *       PRE: filename is atleast 1 character long
 *       POST: metadata is read into variables  */
int readFile(int *** metadataTable, int * metadataAmnt, int * mapRow, int * mapCol, char* filename)
{
    int** metadata;
    int metaDataAmount, mapRows, mapCols, i, successfulRead;

    FILE* filePtr = NULL;
    filePtr = fopen(filename, "r");
    successfulRead = 1;

    if(filePtr == NULL)
    {
        perror("File not found. Please enter a valid filename in the current directory.");
        successfulRead = 0;
    }
    else
    {
        /*read first line to get the metaDataAmount i.e. size of the array*/
        fscanf(filePtr, "%d %d %d", &metaDataAmount, &mapRows, &mapCols);
        
        metadata = (int**)malloc(sizeof(int*) * metaDataAmount);

        for(i = 0; i < metaDataAmount; i++)
        {
            metadata[i] = (int*)malloc(sizeof(int) * 3);
        }

        /*now read in all the metadata row by row*/
        for(i = 0; i < metaDataAmount; i++)
        {
            fscanf(filePtr, "%d %d %d", &metadata[i][0], &metadata[i][1], &metadata[i][2]);
        }

        /*now the metadata needs to be sorted by the object code i.e. 0, then 1, 2 ...*/
        metadata = sortObjectsByCode(metadata, metaDataAmount, mapRows, mapCols);

        if(ferror(filePtr))
        {
            perror("Could not read file");
            successfulRead = 0;

        }

        fclose(filePtr);
        filePtr = NULL;
    }

    /*assigning the main function's data to the newly read data*/
    *metadataTable = metadata;
    *metadataAmnt = metaDataAmount;
    *mapRow = mapRows;
    *mapCol = mapCols;

    return successfulRead;
}


/*  NAME: sortObjectsByCode
 *  PURPOSE: Sort metadata objects in ascending order by object code
 *  IMPORTS: metadata(address which returned data will be stored),
    metadataAmount(number of objects in the file), mapRow(address where 
    number of rows will be stored), mapCol(address where number of columns
    will be stored)
 *  EXPORTS: sortedMetadata (address of the newly sorted metadata)
 *  ASSERTIONS: 
 *       PRE: metadata is stored in 'metadata'
 *       POST: metadata is sorted in ascending order  */
int** sortObjectsByCode(int** metadata, int metadataAmount, int mapRows, int mapCols)
{
    int i, j;
    int** sortedMetadata = (int**)malloc(sizeof(int*) * metadataAmount);

    for(i = 0; i < metadataAmount; i++)
    {
        sortedMetadata[i] = (int*)malloc(sizeof(int) * 3);
    }

    /*find the player, snake and goal*/
    for(i = 0; i < metadataAmount; i++)
    {
        /*the player*/
        if(metadata[i][2] == 0)
        {
            addToSorted(sortedMetadata, metadata, 0, i);
        }

        /*the snake*/
        if(metadata[i][2] == 1)
        {
            addToSorted(sortedMetadata, metadata, 1, i);
        }

        /*the goal*/
        if(metadata[i][2] == 2)
        {
            addToSorted(sortedMetadata, metadata, 2, i); 
        }
    }

    /*now fill in the metadataAmount - 3 spots with the obstacles*/
    j = 3;
    for(i = 0; i < metadataAmount; i++)
    {
        if(metadata[i][2] == 3)
        {  
            addToSorted(sortedMetadata, metadata, j, i);       
            j++;
        }
    }

    /*free the original unsorted metadata*/
    free2dIntArray(metadataAmount, &metadata);

    return sortedMetadata;
}


/*  NAME: addToSorted
 *  PURPOSE: To move unsorted data to a sorted array
 *  IMPORTS: sortedMetadata(the address where the sorted data will go),
    originalMetadata(the unsorted data), sortedIndex(the index of the sorted
    array's current insert position), originalIndex(the current index of the 
    unsorted array)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: unsorted metadata is stored in 'originalMetadata'
 *       POST: sorted metadata is copied into sortedMetadata  */
void addToSorted(int** sortedMetadata, int** originalMetadata, int sortedIndex, int originalIndex)
{
    sortedMetadata[sortedIndex][0] = originalMetadata[originalIndex][0];
    sortedMetadata[sortedIndex][1] = originalMetadata[originalIndex][1];
    sortedMetadata[sortedIndex][2] = originalMetadata[originalIndex][2]; 
}
