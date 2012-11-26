#include <stdio.h>
#include <math.h>
#include <limits.h>
#include "job_loader.h"
#include "IO_manager.h"
#include "schedule.h"
#include "stats.h"

int main()
{
    long clock = 0;
    int running = 1;
    int time_CPU=INT_MAX;
    int time_IO=INT_MAX;
    int time_Arrival = INT_MAX;
    int noMoreJobs = 0;
    int min;
    /*Job for arrivals*/
    JobP temp_job;
    JobP finished_job;
    /*Initialize Job Loader*/
    next_job(-1);
    /*Initialize IO_manager*/
    IO_init();
    /*Initialize the Scheduler*/
    schedule_init();
    /*Initialize the STATs*/
    init_stats();
    /*Enter the main loop*/
    printf("Start Simulation **\n\n");
    while(running==1)
    {
        printf("*************************************\n");
        time_CPU = next_CPU(clock);
        time_IO = next_CompletedIO(clock);
        /*Must account for if we are at the end of the file*/
        if(noMoreJobs == 0)
        {
            time_Arrival = next_JobArrival(clock);
        }
        if(time_Arrival == -1)
        {
            noMoreJobs = 1;
            time_Arrival = INT_MAX;
        }
        /*increment clock the smallest needed*/
        min = (time_IO < time_Arrival) ? time_IO : time_Arrival;
        clock += (time_CPU < min) ? time_CPU : min;
        if(time_IO == INT_MAX && time_CPU == INT_MAX && time_Arrival == INT_MAX)
        {
             break;
        }
        /*printf("CLOCK: %lu\n",clock);*/
        printf("IO:%i CPU:%i ARR:%i\n",time_IO, time_CPU, time_Arrival);
        printf("Current clock:%lu\n\n",clock);
        if(time_CPU <= time_IO && time_CPU <= time_Arrival)
        {
            /*Handle context switch*/
            temp_job = CPU_finished(clock);
            /*Add to IO if needed*/
            if(temp_job != NULL && temp_job->IOOperations>0)
	    {
                printf("Sent %s to IO\n",temp_job->cmd_name);
                needs_IO(clock,temp_job);
            }
            if(temp_job != NULL && temp_job->IOOperations==0)
	    {
                printf("%s finished\n",temp_job->cmd_name);
                stats_Job(temp_job,clock);
            }
            temp_job = NULL;
        }
        if(time_IO <= time_Arrival && time_IO <= time_CPU)
        {
            /*Handle finishing IO*/
            temp_job = IO_finished(clock);
            if(temp_job != NULL && temp_job->time_remaining>0)
	    {
                printf("Sent %s from IO to CPU\n",temp_job->cmd_name);
                needs_CPU(clock,temp_job);
            }
            if(temp_job != NULL && temp_job->time_remaining==0)
            {
                printf("%s finished\n",temp_job->cmd_name);
                stats_Job(temp_job,clock);
            }
            temp_job = NULL;
        }
        if(time_Arrival <= time_IO && time_Arrival <= time_CPU)
        {
            /*Handle arriving Jobs*/
            do{
                temp_job = next_job(clock);
                if(temp_job!=NULL)
                {
                    printf("Sent %s to CPU\n",temp_job->cmd_name);
                    needs_CPU(clock, temp_job);
                }
            }while(temp_job != NULL);
            temp_job = NULL;
        }
        temp_job = NULL;
        /*Print current queues*/
        printf("\n");
        print_IO_manager();
        printf("\n");
        print_schedule_manager();
        printf("\n");
        printf("*************************************\n");
        clock++;
    }
    print_stats();
    return 0;
}
