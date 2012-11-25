#include "job_queue.h"

#ifndef cs537_IO_manager
#define cs537_IO_manager
typedef struct cs537_IO_manager /*Tag for the struct*/
{ 
    JobQueue waiting_jobs;
    Job current_job;
    int time_left;
}*IO_manager;/*Actual struct name*/
#endif

IO_manager init();

void needs_IO(IO_manager, Job);
