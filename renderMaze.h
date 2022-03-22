#ifndef RENDERMAZE_H
#define RENDERMAZE_H

#define WITHIN_VISIBILITY(startRowCord, endRowCord, startColCord, endColCord) ((i >= startRowCord && i < endRowCord) && (j >= startColCord && j < endColCord))

/*void printMaze(char*** pMaze, int r, int c, int view, int*** table);
void printHiddenMaze(char**** pMaze, int r, int c, int pView, int**** pTable);*/
void printVisibleMaze(char**** pMaze, int r, int c);

#endif