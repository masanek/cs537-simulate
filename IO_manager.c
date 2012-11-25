#include <stdlib.h>
#include "IO_manager.h"

void IO_init()
{
    waiting_jobs = create_JobQueue();
    current_job = NULL;
    time_left = 0;
}

void needs_IO(Job toAdd)
{
    push_JobQueue(waiting_jobs, toAdd);
}


