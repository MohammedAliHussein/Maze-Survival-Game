/*  FILE: renderMaze.c
 *  AUTHOR: Mohammed-Ali Hussein 
 *  STUDENT ID: 20184133
 *  UNIT: COMP 1000 
 *  PURPOSE: To render the maze and it's contents
 *  LAST MOD: 27/08/21
 *  REFERENCE: Submitted for assignment 1 COMP 1000 2021 semester 2 
 *  REQUIRES: renderMaze.h */


#include <stdio.h>
#include <stdlib.h>
#include "renderMaze.h"


/*  NAME: printVisibleMaze
 *  PURPOSE: Print a maze with completed view of obstacles
 *  IMPORTS: r(rows), c(columns), pMaze(address of maze)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: pMaze has been alocated memory and metadata
 *       POST: Entire maze has been printed  */
void printVisibleMaze(char**** pMaze, int r, int c)
{
    char** maze = **pMaze;
    int i, j;

    for(i=0; i<r; i++)
    {
        for(j=0; j<c; j++) 
        {      
            printf("%c", maze[i][j]);  
        }
        printf("\n");
    }  
}


