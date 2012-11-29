#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <stdio.h>

#include "job.h"

JobP create_job(char * name, int start, double CPU_time, int IO_count)
{
    JobP temp_job = (JobP)malloc(sizeof(Job));
    /*TRACE FILE INFO*/
    temp_job->cmd_name = (char*)malloc(sizeof(char)*61);
    temp_job->cmd_name = strcpy(temp_job->cmd_name,name);
    temp_job->arrival_time = start;
    temp_job->CPU_time = (CPU_time*1000);
    temp_job->IO_count = IO_count;
    /*HELPER INFO*/
    /*Time left thats needed on CPU*/
    temp_job->time_remaining = (int)temp_job->CPU_time;
    /*?*/
    temp_job->time_running = 0;
    /*Number of IO ops needed*/
    temp_job->IOOperations = trunc ((IO_count + 8191) / 8192);
    /*Interval of IO rounded up-We should get rid of this and use tim's mod algo(?)*/
    temp_job->IO_interval = trunc(temp_job->CPU_time/temp_job->IOOperations)<1 ? 1 : trunc(temp_job->CPU_time/temp_job->IOOperations);
    /*keep track of when it needs IO for returning from CPU_finished*/
    temp_job->needs_IO = 0;
    /*Print what was loaded*/
    printf("READ IN JOB:%s,Arrival: %i, IOOperations: %f, interval:%f\n",temp_job->cmd_name,start, temp_job->IOOperations, temp_job->IO_interval);
    return temp_job;
}
