/*  FILE: updateMaze.c
 *  AUTHOR: Mohammed-Ali Hussein 
 *  STUDENT ID: 20184133
 *  UNIT: COMP 1000 
 *  PURPOSE: To update the maze per player move.
 *  LAST MOD: 23/09/21
 *  REFERENCE: Submitted for assignment 1 COMP 1000 2021 semester 2 
 *  REQUIRES: updateMaze.h mazeSetup.h terminal.h freeMemory.h renderMaze.h objectCodes.h snakeMovement.h LinkedList.h mazeEntityStates.h*/


#include <stdio.h>
#include <stdlib.h>
#include "updateMaze.h"
#include "mazeSetup.h"
#include "terminal.h"
#include "renderMaze.h"
#include "objectCodes.h"
#include "snakeMovement.h"
#include "LinkedList.h"
#include "mazeEntityStates.h"
#include "freeMemory.h"


/*  NAME: gameLoop
 *  PURPOSE: To re-run/ render the game until 
    the player move onto the goal co-ordinate.
 *  IMPORTS: r(rows), c(columns), pTableData(address of metadataTable),
    metaDataAmount, pMaze(address of maze), view(square of vision for player)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: metadata was retrieved and maze has been allocated memory
 *       POST: The game has been won  */
void gameLoop(int r, int c, int**** pTableData, int metaDataAmount, char*** pMaze)
{
    char** rows = *pMaze;
    int** table = **pTableData;
    char input = ' ';
    LinkedList* pastStates = createLinkedList();

    /*initial setup before first input*/
    updateScreen(r, c, &table, metaDataAmount, &rows, input, pastStates);

    /*the main game loop operates here*/
    while(table[2][2] == GOAL && table[0][2] != SNAKE)
    {  
        disableBuffer();
        scanf(" %c", &input);
        enableBuffer();

        if(VALID_INPUT(input))
        {
            updateScreen(r, c, &table, metaDataAmount, &rows, input, pastStates);
        }   
    }

    if(table[0][2] != SNAKE)
    {
        printf("You Won!\n");
    }
    else
    {
        printf("You Lost.\n");
    }

    freeLinkedList(pastStates, &freeEntityStateArrays); 
}


/*  NAME: updateScreen
 *  PURPOSE: Updated the maze/screen every move.
 *  IMPORTS: r(rows), c(columns), pTableData(address of metadataTable),
    metaDataAmount, pMaze(address of maze), input(direction player chose to move)
    pastStates(previous states the game's entities held)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: metadata was retrieved and maze has been allocated memory
 *       POST: The new maze has been printed to the terminal  */
void updateScreen(int r, int c, int*** pTableData, int metaDataAmount, char*** pMaze, char input, LinkedList* pastStates)
{
    char** rows = *pMaze;
    int** table = *pTableData;

    system("clear");
    updateGameState(input, table, pastStates, rows);
    setupBoundaries(r, c, &rows);
    setupMetadata(&table, metaDataAmount, &rows);
    printVisibleMaze(&pMaze, r, c);
}


/*  NAME: updateGameState
 *  PURPOSE: Update the state of the game's entities
 *  IMPORTS: table(address of metadataTable),rows(address of maze),
    pastStates(previous states the game's entities held),
    input(direction player chose to move)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: metadata was retrieved and maze has been allocated memory
 *       POST: The new maze state has been updated  */
void updateGameState(char input, int** table, LinkedList* pastStates, char** rows)
{
    mazeEntitiesState* entityStates = NULL;

    /* the first time the game runs, there is no maze by this point, therefore input will cause an uninitialised error
    trying to access the maze so ignore the input for the first time the game renders*/
    if(input != ' ')
    {
        if(input != 'u')
        {
            addToPastStates(table, pastStates);
            updatePlayerPosition(&table, input, &rows); 
            updateSnakePosition(&table, &rows);     
        }
        else /*the user presses 'u'*/
        {
            entityStates = (mazeEntitiesState*)removeLast(pastStates);
            
            /*if entityStates is null, that means the linked list is empty*/
            if(entityStates != NULL)
            {
                revertEntityStates(entityStates, table);
                free(entityStates->playerEntityState);
                free(entityStates->snakeEntityState);
                free(entityStates);
            }
        }
    }
    else
    {
        /*the first time the game runs, we want to store the starting state of the game without taking input*/
        addToPastStates(table, pastStates);
    }    
}


/*  NAME: updatePlayerPosition                                    
 *  PURPOSE: Update player's metadata co-ordinates
 *  IMPORTS: pMaze(address of maze), tableData(address of metadata),
    move(move direction)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: Player has made a move
 *       POST: Player position is updated according to move  */
void updatePlayerPosition(int*** tableData, char move, char*** pMaze)
{
    char** maze = *pMaze;
    int** table = *tableData;    

    int playerRow = table[0][0]; 
    int playerCol = table[0][1]; 

    switch(move)
    {
        /*per move, checking if the player is allowed to move in that direction
        or if that 'move' is the winning move*/
        case 'w':
            if(maze[playerRow-1][playerCol] == ' ' || maze[playerRow-1][playerCol] == 'x')
            {
                if(maze[playerRow-1][playerCol] == 'x')
                {
                    updateWinMetadata(&table, UP_ARROW);
                    updatePlayerArrow(&table, UP_ARROW);
                }
                else
                {
                    updatePlayerCoordinates(&table, playerRow - 1, playerCol);
                    updatePlayerArrow(&table, UP_ARROW);                      
                }
            }
            break;
        case 'a':
            if(maze[playerRow][playerCol-1] == ' ' || maze[playerRow][playerCol-1] == 'x')
            {
                if(maze[playerRow][playerCol-1] == 'x')
                {
                    updateWinMetadata(&table, LEFT_ARROW);
                    updatePlayerArrow(&table, LEFT_ARROW); 
                }
                else
                {
                    updatePlayerCoordinates(&table, playerRow, playerCol - 1);
                    updatePlayerArrow(&table, LEFT_ARROW);                    
                }                
            }
            break;
        case 's':
            if(maze[playerRow+1][playerCol] == ' ' || maze[playerRow+1][playerCol] == 'x')
            {
                if(maze[playerRow+1][playerCol] == 'x')
                {
                    updateWinMetadata(&table, DOWN_ARROW);
                    updatePlayerArrow(&table, DOWN_ARROW); 
                }
                else
                {
                    updatePlayerCoordinates(&table, playerRow + 1, playerCol);
                    updatePlayerArrow(&table, DOWN_ARROW);                     
                }                
            }
            break;
        default:
            if(maze[playerRow][playerCol+1] == ' ' || maze[playerRow][playerCol+1] == 'x')
            {
                if(maze[playerRow][playerCol+1] == 'x')
                {
                    updateWinMetadata(&table, RIGHT_ARROW);
                    updatePlayerArrow(&table, RIGHT_ARROW); 
                }
                else
                {
                    updatePlayerCoordinates(&table, playerRow, playerCol + 1);
                    updatePlayerArrow(&table, RIGHT_ARROW);                   
                }      
            }
            break;
    }

}


/*  NAME: updateWinMetadata
 *  PURPOSE: Update goal/ 'x' metdata when player wins
 *  IMPORTS: metadataTable(address of metadata), type(which
    arrow/player model i.e. < or ^ or > etc)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: Player has moved onto win poistion
 *       POST: Goal metadata type updated to player */
void updateWinMetadata(int*** metadataTable, int type)
{
    int** table = *metadataTable;
    /*changing the x/ goal co-ordinate to an arrow*/
    table[2][2] = type; 

    table[0][0] = table[1][0];
    table[0][1] = table[1][1];
}


/*  NAME: updatePlayerCoordinates
 *  PURPOSE: Update player metdata co-ordinates on move
 *  IMPORTS: metadataTable(address of metadata), r(player row),
    c(player column)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: Player has moved
 *       POST: Player metadata updated */
void updatePlayerCoordinates(int*** metadataTable, int r, int c)
{
    int** table = *metadataTable;
    /*new player row pos*/
    table[0][0] = r; 
    /*new player col pos*/
    table[0][1] = c;
}


/*  NAME: updatePlayerArrow
 *  PURPOSE: Update player metdata symbol
 *  IMPORTS: metadataTable(address of metadata), 
    arrowType(corresponds to ^ or > etc)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: Player has moved
 *       POST: Player metadata updated */
void updatePlayerArrow(int*** metadataTable, int arrowType)
{
    int** table = *metadataTable;
    /*updating player arrow direction i.e. ^ or < etc*/
    table[0][2] = arrowType;  
}


/*  NAME: copyPlayerEntityMetadata
 *  PURPOSE: Retreive player entity state data 
 *  IMPORTS: originalData(address of the current state
    metadata)
 *  EXPORTS: playerMetadata(address of players data)
 *  ASSERTIONS: 
 *       PRE: Player has metadata in originalData
 *       POST: playerMetadata is returned for the current state */
int* copyPlayerEntityMetadata(int** originalData)
{
    /*memory is 3 ints instead of 2d array because freeing will be easier later*/
    int* playerMetadata = (int*)malloc(sizeof(int) * 3);

    /*copying player row, column and arrow data*/
    playerMetadata[0] = originalData[0][0];
    playerMetadata[1] = originalData[0][1];
    playerMetadata[2] = originalData[0][2];

    return playerMetadata;
}


/*  NAME: copySnakeEntityMetadata
 *  PURPOSE: Retreive snake entity state data 
 *  IMPORTS: originalData(address of the current state
    metadata)
 *  EXPORTS: snakeMetadata(address of snake's data)
 *  ASSERTIONS: 
 *       PRE: snake has metadata in originalData
 *       POST: snakeMetadata is returned for the current state */
int* copySnakeEntityMetadata(int** originalData)
{
    int* snakeMetadata = (int*)malloc(sizeof(int) * 2);

    /*copying snake row and column data*/
    snakeMetadata[0] = originalData[1][0];
    snakeMetadata[1] = originalData[1][1];

    return snakeMetadata;
}


/*  NAME: addToPastStates
 *  PURPOSE: Add current state of snake and player entities to 
    linked list of entity states
 *  IMPORTS: currentDataState(address of the current state
    metadata), pastStates(address of linked list with all past states of 
    the game)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: currentDataState is initialised with metadata
 *       POST: entity states are added to the end of the pastStates linked list */
void addToPastStates(int** currentDataState, LinkedList* pastStates)
{
    /*copy the maze state to a new array*/
    int* copiedPlayerEntity = copyPlayerEntityMetadata(currentDataState);
    int* copiedSnakeEntity = copySnakeEntityMetadata(currentDataState);

    /*allocated memory for a new struct to hold the states*/
    mazeEntitiesState* currentStates = (mazeEntitiesState*)malloc(sizeof(mazeEntitiesState));

    /*store the copied data into the new struct*/
    currentStates->playerEntityState = copiedPlayerEntity;
    currentStates->snakeEntityState = copiedSnakeEntity;

    /*insert the struct holding the maze state into the end of the LinkedList*/
    insertLast(pastStates, currentStates);

    /*now LinkedList should have the currentState stored in a new node at the end of the LinkedList*/
}


/*  NAME: revertEntityStates
 *  PURPOSE: Set entity states to the previous player input and 
    previous snake movement
 *  IMPORTS: table(address of the current state
    metadata), entityStates(address of the entity states from 1 user 
    input prior)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: table is initialised with metadata and entityStates is not null
 *       POST: entity states are reverted to the previous user input state */
void revertEntityStates(mazeEntitiesState* entityStates, int** table)
{
    /*player past state*/
    table[0][0] = entityStates->playerEntityState[0];
    table[0][1] = entityStates->playerEntityState[1];
    table[0][2] = entityStates->playerEntityState[2];

    /*snake past state*/
    table[1][0] = entityStates->snakeEntityState[0];
    table[1][1] = entityStates->snakeEntityState[1]; 
}

