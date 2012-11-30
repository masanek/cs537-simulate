#include "stats.h"
#include "job.h"
#include <stdio.h>
#include <limits.h>
/*What we print out*/
static double AVERAGE_COMPLETION;
static double MAX_COMPLETION;
static double MIN_COMPLETION;
static double THROUGHPUT;
static double UTILIZATION; /*No idea about this one*/
/*Helper variables*/
static int total_jobs;
static int final_clock;
static int total_computation;

void init_stats()
{
    AVERAGE_COMPLETION = 0.0;
    MAX_COMPLETION = 0.0;
    MIN_COMPLETION = (double)INT_MAX;
    THROUGHPUT = 0.0;
    UTILIZATION = 0.0;
    total_jobs = 0;
    final_clock = 0;
    total_computation = 0;
}

void stats_Job(JobP job, int current_time)
{
    /*Just going to do Average completion now*/
    AVERAGE_COMPLETION = (AVERAGE_COMPLETION*total_jobs+(current_time-job->arrival_time))/(total_jobs+1);
    total_jobs++;
    /*Check for min or max*/
    if(MIN_COMPLETION>current_time-job->arrival_time)
    {
        MIN_COMPLETION = (double)current_time-job->arrival_time;
    }
    if(MAX_COMPLETION<current_time-job->arrival_time)
    {
        MAX_COMPLETION = (double)current_time-job->arrival_time;
    }
    total_computation += job->CPU_time;
}

void print_stats(long final_clock)
{
    printf("**********STATISTICS************\n");
    printf("FINAL TIME:%lu\n",final_clock);
    printf("AVERAGE COMPLETION TIME:%f\n",AVERAGE_COMPLETION);
    printf("MIN COMPLETION TIME:%f\n",MIN_COMPLETION);
    printf("MAX COMPLETION TIME:%f\n",MAX_COMPLETION);
    printf("THROUGHPUT:%f\n",((double)total_jobs)/((double)final_clock/1000.0));
    printf("UTILIZATION:%f\n", (double)total_computation/(double)final_clock);
}
