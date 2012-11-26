#include "job_queue.h"

void IO_init();

void needs_IO(int, JobP);

int next_CompletedIO(int);

JobP IO_finished(int);

void print_IO_manager();
