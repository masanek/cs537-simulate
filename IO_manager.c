#include <stdlib.h>
#include "IO_manager.h"


static JobQueue waiting_jobs;
static Job current_job;
static int time_started;

void IO_init()
{
    waiting_jobs = create_JobQueue();
    current_job = NULL;
    time_started = 0;
}

void needs_IO(Job toAdd)
{
    push_JobQueue(waiting_jobs, toAdd);
}

int next_CompletesIO(int current_time)
{
    return 10-(current_time - time_started);
}



