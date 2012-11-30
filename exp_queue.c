#include <stdlib.h>
#include "exp_queue.h"
#include "job_queue.h"


ExpQueueP create_ExpQueue(){
  ExpQueueP temp_queue = malloc(sizeof(ExpQueue));
  int i;
  for (i = 0; i < 8; i++){
     temp_queue->queue[i] = create_JobQueue(); 
  }  

  return temp_queue;

}

void push_ExpQueue(ExpQueueP expQueue, JobP toAdd){

  push_JobQueue(expQueue->queue[toAdd->priorityLevel], toAdd);
  return;

} 
    
JobP pop_ExpQueue(ExpQueueP expQueue){
  JobP temp = NULL;
  int i = 0;
  while(1){
    /* pop next job off highest priority queue, if nothing go to next queue */
    if ((temp = pop_JobQueue(expQueue->queue[i])) == NULL) i++;
    /* if we got something or have looped through everything return */
    if (temp != NULL || i>7) break;  
  } 
  return temp;
}

