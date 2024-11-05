#include "sched.h"
#include "switch.h"
#include <stdlib.h>
#include <limits.h>

extern struct proc proc[];

struct proc* select_next(){
    int next_random = -1;
    struct proc* next = NULL;
    for (int i = 0; i < NUMPROC; i++){
        if (proc[i].status == RUNNABLE){
            int random = rand();
            if (random > next_random){
                next_random = random;
                next = &proc[i];
            }
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