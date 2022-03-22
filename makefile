CC = gcc
CFLAGS = -Wall -pedantic -ansi 
OBJ = main.o terminal.o mazeSetup.o updateMaze.o freeMemory.o renderMaze.o fileIO.o snakeMovement.o LinkedList.o
EXEC = maze

ifdef DEBUG
CFLAGS += -g
endif

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c mazeSetup.h freeMemory.h fileIO.h
	$(CC) -c main.c $(CFLAGS)

terminal.o : terminal.c terminal.h
	$(CC) -c terminal.c $(CFLAGS)

mazeSetup.o : mazeSetup.c mazeSetup.h updateMaze.h objectCodes.h freeMemory.h
	$(CC) -c mazeSetup.c $(CFLAGS)

updateMaze.o : updateMaze.c updateMaze.h mazeSetup.h terminal.h renderMaze.h objectCodes.h snakeMovement.h LinkedList.h mazeEntityStates.h freeMemory.h
	$(CC) -c updateMaze.c $(CFLAGS)

freeMemory.o : freeMemory.c freeMemory.h mazeEntityStates.h
	$(CC) -c freeMemory.c $(CFLAGS)

renderMaze.o : renderMaze.c renderMaze.h
	$(CC) -c renderMaze.c $(CFLAGS)

fileIO.o : fileIO.c fileIO.h freeMemory.h
	$(CC) -c fileIO.c $(CFLAGS)

snakeMovement.o : snakeMovement.c snakeMovement.h objectCodes.h
	$(CC) -c snakeMovement.c $(CFLAGS)

LinkedList.o : LinkedList.c LinkedList.h
	$(CC) -c LinkedList.c $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJ)
