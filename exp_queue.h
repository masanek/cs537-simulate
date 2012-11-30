#include "job_queue.h"

#ifndef exp_queue
#define exp_queue
typedef struct exp_queue {
  JobQueueP queue[8];
} ExpQueue, *ExpQueueP;

#endif

ExpQueueP create_ExpQueue();

void push_ExpQueue(ExpQueueP expQueue, JobP toAdd);

JobP pop_ExpQueue(ExpQueueP q);



