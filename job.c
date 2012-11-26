#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <stdio.h>

#include "job.h"

JobP create_job(char * name, int start, double CPU_time, int IO_count)
{
    JobP temp_job = (JobP)malloc(sizeof(Job));
    /*If they are anal about this we can always make it error proof later*/
    temp_job->cmd_name = (char*)malloc(sizeof(char)*61);
    temp_job->cmd_name = strcpy(temp_job->cmd_name,name);
    temp_job->arrival_time = start;
    temp_job->CPU_time = (int)(CPU_time*1000);
    temp_job->time_remaining = (int)temp_job->CPU_time;
    temp_job->time_running = 0;
    temp_job->IO_count = IO_count;
    temp_job->IOOperations = (int)trunc ((IO_count + 8191) / 8192);
    temp_job->IO_interval = (int)trunc(temp_job->CPU_time/temp_job->IOOperations);
    temp_job->timeTillNextIO = temp_job->IO_interval;
    printf("LOADED JOB:%s,Arrival: %i, IOOperations: %i, interval:%i\n",temp_job->cmd_name,start, temp_job->IOOperations, temp_job->IO_interval);
    return temp_job;
}
