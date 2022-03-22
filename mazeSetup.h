#ifndef MAZESETUP_H
#define MAZESETUP_H

#define FALSE 0
#define TRUE !FALSE

void setupMaze(int r, int c, int*** tableData, int metaDataAmount);
void setupBoundaries(int rows, int columns, char*** dynamicMaze);
void setupMetadata(int*** metadataMatrix, int metaDataAmount, char*** mazeTable);

#endif