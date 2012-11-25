#include "job.h"

/*Holder for next job*/
static Job waiting_job = NULL;

Job next_job(int);

int time_till_next(int);
