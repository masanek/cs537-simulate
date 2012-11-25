/*Define our job struct, but not twice*/
#ifndef cs537_Job
#define cs537_Job
typedef struct cs537_Job /*Tag for the struct*/
{ 
    char* cmd_name;
    int arrival_time;
    int start_time;
    int CPU_time;
    int time_remaining;
    int time_running;
    int IO_count;
    int IOOperations;
    int IO_interval;
}*Job;/*Actual struct name*/
#endif

Job create_job(char *, int, double, int);
