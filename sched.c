#include "sched.h"
#include "switch.h"
#include <stdlib.h>
#include <limits.h>

extern struct proc proc[];

struct proc* select_next(){
    float min_runtime = INT_MAX;
    struct proc *next = NULL;
    for (int i = 0; i < NUMPROC; i++){
        if (proc[i].status == RUNNABLE && proc[i].runtime < min_runtime){
            min_runtime = proc[i].runtime;
            next = &proc[i];
        }
    }
    return next;
}

void scheduler(){
    while (!done()){
        struct proc *candidate = select_next();

        if (candidate != NULL) {
            candidate->status = RUNNING;
            candidate->runtime += swtch(candidate);
        } else {
            idle();
        }
    }
}