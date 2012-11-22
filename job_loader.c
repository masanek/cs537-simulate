#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "job_loader.h"

void next_job(int current_time)
{
    int buffer_size = 60;
    char next_line[60];
    char * command_name;
    int start_time;
    double cpu_time;
    int IO_count;
    /*Get the next line from the file*/
    fgets(next_line,buffer_size, stdin);
    /*Chop it up by the spaces*/
    command_name = strtok(next_line," ");
    start_time = atoi(strtok(NULL," "));
    cpu_time = atof(strtok(NULL," "));
    IO_count = atoi(strtok(NULL," "));
    /*TODO:Create the job*/
    printf("%s,%i,%f,%i\n",command_name,start_time,cpu_time,IO_count);
}
