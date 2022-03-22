#ifndef UPDATEMAZE_H
#define UPDATEMAZE_H

#include "LinkedList.h"
#include "mazeEntityStates.h"

#define VALID_INPUT(x) (x == 'w') || (x == 'a') || (x == 's') || (x == 'd') || (x == 'u')

void gameLoop(int r, int c, int**** pTableData, int metaDataAmount, char*** pRows);
void updateScreen(int r, int c, int*** pTableData, int metaDataAmount, char*** pMaze, char pInput, LinkedList* pastStates);
void updateGameState(char input, int** table, LinkedList* pastStates, char** rows);
void updatePlayerPosition(int*** tableData, char input, char*** pMaze);
void updateWinMetadata(int*** metadataTable, int type);
void updatePlayerCoordinates(int*** metadataTable, int r, int c);
void updatePlayerArrow(int*** metadataTable, int arrowType);
int* copyPlayerEntityMetadata(int** originalData);
int* copySnakeEntityMetadata(int** originalData);
void addToPastStates(int** currentDataState, LinkedList* pastStates);
void revertEntityStates(mazeEntitiesState* entityStates, int** table);

#endif