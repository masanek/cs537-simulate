#include "job_queue.h"

void schedule_init();

void needs_CPU(int,JobP);

int next_CPU(int);

JobP CPU_finished(int);

JobP getCurrentJob();

void print_schedule_manager();
