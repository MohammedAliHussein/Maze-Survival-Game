/*  FILE: snakeMovement.c
 *  AUTHOR: Mohammed-Ali Hussein 
 *  STUDENT ID: 20184133
 *  UNIT: COMP 1000 
 *  PURPOSE: To update the snake's position per user input
 *  LAST MOD: 22/09/21
 *  REQUIRES: snakeMovement.h objectCodes.h */


#include <stdio.h>
#include <stdlib.h>
#include "snakeMovement.h"
#include "objectCodes.h"


/*  NAME: updateSnakePosition
 *  PURPOSE: Change the snake's position relative to the player's position
    even if the player does not make a net change in distance since the last input
 *  IMPORTS: pTableData(address of metadataTable),
    pMaze(address of the character array of the game)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: maze has been initialised an atleast 1 move has been made
            by the player
 *       POST: snake moves closer to the player  */
void updateSnakePosition(int*** pTableData, char*** pMaze)
{
    int** mazeData = *pTableData;
    char** maze = *pMaze;

    int snakeRow = mazeData[1][0];
    int snakeCol = mazeData[1][1];

    int playerRow = mazeData[0][0];
    int playerCol = mazeData[0][1];

    /*if snake is above player*/
    if(snakeRow < playerRow)
    {
        moveSnakeDown(mazeData, maze);
    }
    /*if snake is below player*/
    else if(snakeRow > playerRow)
    {
        moveSnakeUp(mazeData, maze);
    }
    /*if snake is in line with player*/
    else
    {
        /*if in the same row, left or right? */
        /*if snake is same row, but left*/
        if(snakeCol < playerCol)
        {
            moveSnakeRight(mazeData, maze);
        }
        /*if snake is same row, but right (snakeCol > playerCol)*/
        if(snakeCol > playerCol)
        {
            moveSnakeLeft(mazeData, maze);
        }
    }
}


/*  NAME: moveSnakeDown
 *  PURPOSE: Move the snake 1 unit down if no obstalces
 *  IMPORTS: mazeData(address of metadataTable),
    maze(address of the character array of the game)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: maze has been initialised
 *       POST: snake moves down closer to the player  */
void moveSnakeDown(int** mazeData, char** maze)
{
    /*purpose is to check if boundaries are in the way*/
    int oneUnitDownRow = mazeData[1][0] + 1;
    int snakeCol = mazeData[1][1];

    /*wont have to check for boundary of the wall because the player cannot be lower than the wall*/
    if(PLAYER_OR_EMPTY(maze[oneUnitDownRow][snakeCol]))
    {
        mazeData[1][0] = oneUnitDownRow;
        checEndGame(mazeData, maze);
    }
}


/*  NAME: moveSnakeUp
 *  PURPOSE: Move the snake 1 unit up if no obstalces
 *  IMPORTS: mazeData(address of metadataTable),
    maze(address of the character array of the game)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: maze has been initialised
 *       POST: snake moves up closer to the player  */
void moveSnakeUp(int** mazeData, char** maze)
{
    /*purpose is to check if boundaries are in the way*/
    int oneUnitUpRow = mazeData[1][0] - 1;
    int snakeCol = mazeData[1][1];

    /*wont have to check for boundary of the wall because the player cannot be above than the wall*/
    if(PLAYER_OR_EMPTY(maze[oneUnitUpRow][snakeCol]))
    {
        mazeData[1][0] = oneUnitUpRow;
        checEndGame(mazeData, maze);
    }
}


/*  NAME: moveSnakeRight
 *  PURPOSE: Move the snake 1 unit right if no obstalces
 *  IMPORTS: mazeData(address of metadataTable),
    maze(address of the character array of the game)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: maze has been initialised
 *       POST: snake moves right closer to the player  */
void moveSnakeRight(int** mazeData, char** maze)
{
    /*purpose is to check if boundaries are in the way*/
    int snakeRow = mazeData[1][0];
    int oneUnitRightCol = mazeData[1][1] + 1;

    /*wont have to check for boundary of the wall because the player cannot be further right than the wall*/
    if(PLAYER_OR_EMPTY(maze[snakeRow][oneUnitRightCol]))
    {
        mazeData[1][1] = oneUnitRightCol;
        checEndGame(mazeData, maze);
    }
}


/*  NAME: moveSnakeLeft
 *  PURPOSE: Move the snake 1 unit left if no obstalces
 *  IMPORTS: mazeData(address of metadataTable),
    maze(address of the character array of the game)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: maze has been initialised
 *       POST: snake moves left closer to the player  */
void moveSnakeLeft(int** mazeData, char** maze)
{
    /*purpose is to check if boundaries are in the way*/
    int snakeRow = mazeData[1][0];
    int oneUnitLeftCol = mazeData[1][1] - 1;

    /*wont have to check for boundary of the wall because the player cannot be further left than the wall*/
    if(PLAYER_OR_EMPTY(maze[snakeRow][oneUnitLeftCol]))
    {
        mazeData[1][1] = oneUnitLeftCol;
        checEndGame(mazeData, maze);
    }
}


/*  NAME: checEndGame
 *  PURPOSE: Check if the player and snake are on 
    the same co-ordinate and change the metadata code
    of the player if the two co-ordinates are the same
 *  IMPORTS: mazeData(address of metadataTable),
    maze(address of the character array of the game)
 *  EXPORTS: none
 *  ASSERTIONS: 
 *       PRE: maze has been initialised and snake has moved
 *       POST: snake and player have the same metadata code if their
         co-ordinate position is the same    */
void checEndGame(int** mazeData, char** maze)
{
    /*game ends/ exits loop by player character becoming the snake
    i.e. position of snake and player are the same*/
    int playerRow = mazeData[0][0];
    int playerCol = mazeData[0][1];
    int snakeRow = mazeData[1][0];
    int snakeCol = mazeData[1][1];

    if((playerRow == snakeRow) && (playerCol == snakeCol))
    {
        /*now change the player to ~*/
        mazeData[0][2] = SNAKE;        
    }
}
