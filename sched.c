#include "sched.h"
#include "switch.h"
#include <stdlib.h>
#include <limits.h>

extern struct proc proc[];

struct proc* select_next(){
    int n = rand() % NUMPROC;
    if (proc[n].status == RUNNABLE) {
        return &proc[n];
    }
    return NULL;
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