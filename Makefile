CC = gcc
RM = rm
TARGET = exc

all: objetos
	$(CC) trabalho.c -o $(TARGET)

objetos: trabalho.c 
	$(CC) -c trabalho.c

clean:
	$(RM) *.o 
	$(RM) $(TARGET)		
