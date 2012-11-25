#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "job.h"

Job create_job(char * name, int start, double CPU_time, int IO_count)
{
    Job temp_job = malloc(sizeof(Job));
    /*If they are anal about this we can always make it error proof later*/
    temp_job->cmd_name = malloc(sizeof(char)*60);
    strcpy(temp_job->cmd_name,name);
    temp_job->arrival_time = start;
    temp_job->start_time = 0;
    temp_job->CPU_time = CPU_time*1000;
    temp_job->time_remaining = temp_job->CPU_time;
    temp_job->time_running = 0;
    temp_job->IO_count = IO_count;
    temp_job->IOOperations = trunc ((IO_count + 8191) / 8192);
    temp_job->IO_interval = trunc(temp_job->CPU_time/temp_job->IOOperations);
    return temp_job;
}
