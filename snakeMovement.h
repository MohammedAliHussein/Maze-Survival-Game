#ifndef SNAKEMOVEMENT_H
#define SNAKEMOVEMENT_H

#define PLAYER_OR_EMPTY(pos) ((pos) == (' ')) || ((pos) == ('<')) || ((pos) == ('v')) || ((pos) == ('>')) || ((pos) == ('^'))

void updateSnakePosition(int*** mazeData, char*** mazeTable);
void moveSnakeDown(int** mazeData, char** maze);
void moveSnakeUp(int** mazeData, char** maze);
void moveSnakeRight(int** mazeData, char** maze);
void moveSnakeLeft(int** mazeData, char** maze);
void checEndGame(int** mazeData, char** maze);

#endif