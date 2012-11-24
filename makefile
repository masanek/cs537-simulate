# Makefile for executable proj2
CC = gcc
CFLAGS = -pedantic -Wall

# ****************************************************
sim: main.o job_queue.o job_loader.o job.o
	$(CC) $(CFLAGS) main.o job_loader.o job_queue.o job.o -o sim -lpthread

job_queue.o: job_queue.c 
	$(CC) $(CFLAGS) -c job_queue.c

job_loader.o: job_loader.c 
	$(CC) $(CFLAGS) -c job_loader.c

job.o: job.c 
	$(CC) $(CFLAGS) -c job.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -lpthread

clean:
	rm main.o job_loader.o job_queue.o job.o
