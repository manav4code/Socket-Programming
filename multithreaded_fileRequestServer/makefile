# Define dependencies
DEP = tcp.o 
TARGET = server client

# Compiler and flags
CC = gcc

# Targets
all: clean $(TARGET)

server: $(DEP) server.c
	$(CC) $(CFLAGS) -o server server.c $(DEP)
	

client: tcp.h tcp.o client.c 
	$(CC) $(CFLAGS) -o client client.c $(DEP)

tcp.o: tcp.h
	$(CC) $(CFLAGS) -c tcp.c


clean:
	rm -f *.o
	rm -f $(TARGET)
	clear