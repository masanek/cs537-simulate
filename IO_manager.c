#include <stdlib.h>

#include "IO_manager.h"

IO_manager init()
{
    IO_manager temp_manager = malloc(sizeof(IO_manager));
    temp_manager->waiting_jobs = create_JobQueue();
    temp_manager->current_job = NULL;
    temp_manager->time_left = 0;
    return temp_manager;
}

void needs_IO(IO_manager manager, Job toAdd)
{
    push_JobQueue(manager->waiting_jobs, toAdd);
}


