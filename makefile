# Makefile for executable proj2
CC = gcc
CFLAGS = -pedantic -Wall

# ****************************************************
sim: main.o job_queue.o job_loader.o job.o IO_manager.o stats.o scheduleTimeSlice.o
	$(CC) $(CFLAGS) main.o job_loader.o job_queue.o job.o IO_manager.o stats.o scheduleTimeSlice.o -o sim -lm -g

scheduleTimeSlice.o: scheduleTimeSlice.c 
	$(CC) $(CFLAGS) -c scheduleTimeSlice.c

schedule.o: schedule.c 
	$(CC) $(CFLAGS) -c schedule.c

IO_manager.o: IO_manager.c 
	$(CC) $(CFLAGS) -c IO_manager.c

job_queue.o: job_queue.c 
	$(CC) $(CFLAGS) -c job_queue.c

job_loader.o: job_loader.c 
	$(CC) $(CFLAGS) -c job_loader.c

job.o: job.c 
	$(CC) $(CFLAGS) -c job.c

stats.o: stats.c 
	$(CC) $(CFLAGS) -c stats.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm main.o job_loader.o job_queue.o job.o IO_manager.o schedule.o stats.o
