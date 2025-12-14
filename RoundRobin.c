#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int pid;
    int burst_time;
    struct process_t *next;
}process_t;

process_t head;
process_t tail;

process_t *createProcess(int pid, int burst_time){
    process_t *p = malloc(sizeof(process_t));
    p->pid = pid;
    p->burst_time = burst_time;

    return p;
}

int main(){

}