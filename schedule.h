#include "job_queue.h"

#ifndef cs537_IO_manager
#define cs537_IO_manager
typedef struct cs537_Scheduler /*Tag for the struct*/
{ 
    JobQueue waiting_jobs;
    Job current_job;
}*Scheduler;/*Actual struct name*/
#endif

Scheduler init();
