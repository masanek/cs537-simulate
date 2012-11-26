#include "stats.h"
#include "job.h"
#include <stdio.h>
/*What we print out*/
static double AVERAGE_COMPLETION;
static double MAX_COMPLETION;
static double MIN_COMPLETION;
static double THROUGHPUT;
static double UTILIZATION; /*No idea about this one*/
/*Helper variables*/
static int total_jobs;
static int final_clock;
static int total_completion;

void init_stats()
{
    AVERAGE_COMPLETION = 0.0;
    MAX_COMPLETION = 0.0;
    MIN_COMPLETION = 0.0;
    THROUGHPUT = 0.0;
    UTILIZATION = 0.0;
    total_jobs = 0;
    final_clock = 0;
    total_completion = 0;
}

void stats_Job(JobP job, int current_time)
{
    /*Just going to do Average completion now*/
    AVERAGE_COMPLETION = (AVERAGE_COMPLETION*total_jobs+(current_time-job->arrival_time))/(total_jobs+1);
    total_jobs++;
}

void print_stats()
{
    printf("**********STATISTICS************\n");
    printf("AVERAGE COMPLETION TIME:%f\n",AVERAGE_COMPLETION);
    
}
