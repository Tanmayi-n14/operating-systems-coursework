#include <stdio.h>
#include <pthread.h>

int main() {
    pthread_attr_t attr;
    int policy;

    pthread_attr_init(&attr); // Initialize with defaults
    pthread_attr_getschedpolicy(&attr, &policy);

    if (policy == SCHED_OTHER) printf("Policy: SCHED_OTHER (Standard Linux)\n");
    else if (policy == SCHED_FIFO) printf("Policy: SCHED_FIFO (Real-time)\n");
    else if (policy == SCHED_RR) printf("Policy: SCHED_RR (Round Robin)\n");

    pthread_attr_destroy(&attr);
    return 0;
}