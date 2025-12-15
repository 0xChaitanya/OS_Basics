#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define quanta 10

typedef struct process_t{
    int pid;
    int burst_time;
    struct process_t *next;
}process_t;

process_t *head = NULL;
process_t *tail = NULL;

int max(int a, int b){
    if (a > b) return a;
    return b;
}

process_t *createProcess(int pid, int burst_time){
    process_t *p = malloc(sizeof(process_t));
    p->pid = pid;
    p->burst_time = burst_time;
    p->next = NULL;

    return p;
}

void enqueue(process_t *p){ // if queue is empty, tail = NULL, so handled that case also
    if (tail == NULL){
        tail = p;
    }
    else{
        tail->next = p;
        tail = p;
    }
}

process_t *dequeue(){ //if queue is empty then NULL will be returned
    process_t *temp = head;
    if (head != NULL){
        head = head->next;
    }
    return temp;
}

void schedule_RR(){
    process_t * iter = head;
    
    while (head != NULL){ //running till queue is empty (i.e. every process finished execution)
        if (iter == NULL) {
            if (max(head->burst_time - quanta, 0) == 0){ // for removing the top process if it finished its time quanta
                process_t *tmp = dequeue();
                free(tmp);
            }
            
            if (head == NULL) break;
            iter = head;
        }
        
        if (iter->next != NULL){
            if (max(iter->next->burst_time, 0) == 0){
                process_t *tmp = iter->next;
                if (iter->next == tail){
                    tail = iter;
                    iter->next = NULL;
                }
                else{
                  iter->next = iter->next->next;
                }
                free(tmp); // freeing the process which has finished its time quanta
            }
        }
        
        iter->burst_time = max(iter->burst_time - quanta, 0);
        printf("%d, Time Left : %d\n", iter->pid, iter->burst_time);
        iter = iter->next;
        sleep(1);
    }
}

int main(){
    process_t *p1 = createProcess(100, 10);
    process_t *p2 = createProcess(101, 20);
    process_t *p3 = createProcess(102, 30);
    
    head = p1;
    p1->next = p2;
    p2->next = p3;
    tail = p3;
    
    
    schedule_RR();
}
