#include <stdlib.h>
#include <string.h>

#include "job.h"

Job create_job(char * name, int start, double CPU_time, int IO_count)
{
    Job temp_job = malloc(sizeof(Job));
    /*If they are anal about this we can always make it error proof later*/
    temp_job->cmd_name = malloc(sizeof(char)*60);
    strcpy(temp_job->cmd_name,name);
    temp_job->start_time = start;
    temp_job->CPU_time = CPU_time;
    temp_job->IO_count = IO_count;
    return temp_job;
}
