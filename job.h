/*Define our job struct, but not twice*/
#ifndef cs537_Job
#define cs537_Job
typedef struct cs537_Job /*Tag for the struct*/
{ 
    char * cmd_name;
    int arrival_time;
    int CPU_time;
    int time_remaining;
    double time_running;
    int IO_count;
    int IOOperations;
    int IO_interval;
    int timeTillNextIO;
}Job,*JobP;/*Actual struct name*/
#endif

JobP create_job(char *, int, double, int);
