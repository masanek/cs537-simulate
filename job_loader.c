#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "job_loader.h"

/*Holder for next job*/
static Job waiting_job = NULL;

Job next_job(int current_time)
{
    /*Return value and variables to creat job*/
    Job return_val = NULL;
    int buffer_size = 60;
    char next_line[60];/*IDK none of them are more then 60 chars*/
    char * command_name;
    int start_time;
    double cpu_time;
    int IO_count;
    /*check if there was a job waiting*/
    if(waiting_job == NULL)
    {
        /*Get the next line from the file*/
        fgets(next_line,buffer_size, stdin);
        /*Chop it up by the spaces*/
        command_name = strtok(next_line," ");
        start_time = atoi(strtok(NULL," "));
        cpu_time = atof(strtok(NULL," "));
        IO_count = atoi(strtok(NULL," "));
        /*Create the job*/
        waiting_job = create_job(command_name,start_time,cpu_time,IO_count);
    }
    /*Check if the job is ok to send*/
    if(waiting_job->start_time <= current_time)
    {
        return_val = waiting_job;
        waiting_job = NULL;
    }
    return return_val;
}

/*Check when the next job arrives*/
int next_JobArrival(int current_time)
{
    /*=Null only if didnt call next_job first or EOF*/
    if(waiting_job != NULL)
    {
        return waiting_job->start_time-current_time;
    }
    else
    {
        return -1;
    }   
}
