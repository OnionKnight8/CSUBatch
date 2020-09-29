CC = gcc
CFLAGS = -I.

all: CSUBatch

# Add source files here
CSUBatch: main.o
	$(CC) -o CSUBatch main.o

# Call 'make clean' to start over.
# Deletes executable and all .o/backup files.
clean:
	$(RM) CSUBatch *.o *~