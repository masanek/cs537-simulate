#include "job_queue.h"

void IO_init();

void needs_IO(int, Job);

int next_CompletedIO(int);

Job IO_finished(int);
