#ifndef FILEIO_H
#define FILEIO_H

int getMetadata(int *** metadataTable, int * metadataAmount, int * mapRow, int * mapCol, char* filename);
int readFile(int *** metadataTable, int * metadataAmnt, int * mapRow, int * mapCol, char* filename);
int** sortObjectsByCode(int** metadata, int metadataAmount, int mapRows, int mapCols);
void addToSorted(int** sortedMetadata, int** originalMetadata, int sortedIndex, int originalIndex);

#endif