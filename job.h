/*Define our job struct, but not twice*/
#ifndef cs537_Job
#define cs537_Job
typedef struct cs537_Job /*Tag for the struct*/
{ 
    char* cmd_name;
    int start_time;
    float CPU_time;
    int IO_count;
}*Job;/*Actual struct name*/
#endif

Job create_job(char *, int, double, int);