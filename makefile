# Makefile for executable proj2
CC = gcc
CFLAGS = -pedantic -Wall

# ****************************************************
sim: main.o job_loader.o
	$(CC) $(CFLAGS) main.o job_loader.o -o sim -lpthread

job_loader.o: job_loader.c 
	$(CC) $(CFLAGS) -c job_loader.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -lpthread

clean:
	rm main.o job_loader.o
