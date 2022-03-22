/*  FILE: mazeSetup.c
 *  AUTHOR: Mohammed-Ali Hussein 
 *  STUDENT ID: 20184133
 *  UNIT: COMP 1000 
 *  PURPOSE: To allocate a dynamic maze 
 *  and assign the maze it's metadata. 
 *  LAST MOD: 27/08/21
 *  REFERENCE: Submitted for assignment 1 COMP 1000 2021 semester 2 
 *  REQUIRES: mazeSetup.h updateMaze.h freeMemory.h objectCodes.h*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mazeSetup.h"
#include "updateMaze.h"
#include "freeMemory.h"
#include "objectCodes.h"


/*  NAME: setupMaze
 *  PURPOSE: dynamically allocate maze memory, call gameLoop and
    de-allocate maze when done
 *  IMPORTS: r(rows), c(columns), tableData(address of metadataTable),
    metaDataAmount, view(square of vision for player)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: metadata was retrieved
 *       POST: de-allocated maze  */
void setupMaze(int r, int c, int*** tableData, int metaDataAmount)
{
    char** mazeRows = (char**)malloc(sizeof(char*) * r); 
    
    /*now per row, columns need to be alocated*/
    int i;
    for(i = 0; i < r; i++)
    {
        mazeRows[i] = (char*)malloc(sizeof(char) * c);
    }

    gameLoop(r, c, &tableData, metaDataAmount, &mazeRows);
    free2dCharArray(r, &mazeRows);
}


/*  NAME: setupBoundaries
 *  PURPOSE: Assign the maze it's boundaries
 *  IMPORTS: r(rows), c(columns), pMaze(address of the maze)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: pMaze was allocated memory
 *       POST: boundaries were added to pMaze  */
void setupBoundaries(int r, int c, char*** pMaze)
{
    int i, j;

    /*contains the address of the first position of the first row */
    char** maze = *pMaze; 

    /*top left corner*/
    maze[0][0] = '#';
    
    /*top right corner*/
    maze[0][c-1] = '#';    
    
    /*bottom left corner*/
    maze[r-1][0] = '#';

    /*bottom right corner*/
    maze[r-1][c-1] = '#';

    /* adding top and bottom boundary */
    /* i+=(r-1) because I only want to fill the first
    row, then jump to the bottom/ r-1th row*/
    for(i=0; i<r; i+=(r-1))
    {
        for(j=1; j<(c-1); j++) /*this was the issue to the 9 columns, was c-2 instead of c-1 */
        {
            maze[i][j] = '-';
        }
    }

    /* adding left and right boundary */
    /* j+=(c-1) because I only want to fill the first
    row, then jump to the bottom/ c-1th column*/
    for(i=1; i<(r-1); i++)
    {
        for(j=0; j<c; j+=(c-1))
        {
            maze[i][j] = '|';           
        }
    }

    /*filling maze with empty space*/
    for(i=1; i<r-1; i++)
    {
        for(j=1; j<c-1; j++)
        {
            maze[i][j] = ' ';
        }
    }
}


/*  NAME: setupMetadata
 *  PURPOSE: Assign the maze it's objects/elements
 *  IMPORTS: metadataMatrix(address of the metdata),
    metaDataAmount, mazeTable(address of the maze)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: pMaze was allocated memory and metadata exists
 *       POST: metadata was added to the maze  */
void setupMetadata(int*** metadataMatrix, int metaDataAmount, char*** mazeTable)
{
    /* metadataMatrix will always be 3x3 for: row,col,type */
    int** metadataTable = *metadataMatrix; 
    char** maze = *mazeTable;

    int i;
    for(i=0; i<metaDataAmount; i++)
    {
        switch(metadataTable[i][2])
        {
            /*assigning each maze co-ordinate a 'symbol' depending on it's
            type identifier in the metadataTable i.e. 0 or 1 or 3 etc*/
            case UP_ARROW: 
                maze[ metadataTable[i][0] ][ metadataTable[i][1] ] = '^';
                break;                
            case SNAKE:
                maze[ metadataTable[i][0] ][ metadataTable[i][1] ] = '~';
                break;
            case GOAL:
                maze[ metadataTable[i][0] ][ metadataTable[i][1] ] = 'x';
                break;
            case OBSTACLE:
                maze[ metadataTable[i][0] ][ metadataTable[i][1] ] = 'o';
                break;
            case DOWN_ARROW:
                maze[ metadataTable[i][0] ][ metadataTable[i][1] ] = 'v';
                break;  
            case RIGHT_ARROW:
                maze[ metadataTable[i][0] ][ metadataTable[i][1] ] = '>';
                break;
            case LEFT_ARROW:
                maze[ metadataTable[i][0] ][ metadataTable[i][1] ] = '<';
                break;               
            default:
                maze[ metadataTable[i][0] ][ metadataTable[i][1] ] = ' ';
                break;                 
        }
    }
}