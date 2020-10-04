CC = gcc
CFLAGS = -o CSUBatch -lpthread -Wall -I.

all: CSUBatch

# Add source files here
CSUBatch: main.o commandline.o scheduling.o dispatching.o jobqueue.o
	$(CC) main.o commandline.o scheduling.o dispatching.o jobqueue.o $(CFLAGS)

# Call 'make jobs' to compile test job files.
jobs:
	$(CC) helloworld.c -o helloworld
	$(CC) process.c -o process
	$(CC) job1.c -o job1

# Call 'make clean' to start over.
# Deletes executable and all .o/backup files.
clean:
	$(RM) CSUBatch *.o *~

# Call 'make cleanjobs' to delete test jobs.
cleanjobs:
	$(RM) process job1 helloworld