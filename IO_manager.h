#include "job_queue.h"

static JobQueue waiting_jobs;
static Job current_job;
static int time_left;

void IO_init();

void needs_IO(Job);
