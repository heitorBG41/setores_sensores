CC = gcc
RM = rm
TARGET = exc

all: objetos
	$(CC) trabalho.o utlidade.o menu.o -o $(TARGET)

objetos: 
	$(CC) -c utlidade.c -o utlidade.o
	$(CC) -c menu.c -o menu.o
	$(CC) -c trabalho.c -o trabalho.o
clean:
	$(RM) *.o 
	$(RM) $(TARGET)		
