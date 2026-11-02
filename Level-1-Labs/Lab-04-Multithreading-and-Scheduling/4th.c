#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* stay_alive(void* arg) {
    while(1) sleep(1); // Keep thread active
    return NULL;
}

int main() {
    pthread_t t[4];
    printf("My PID is: %d\n", getpid());
    for(int i=0; i<4; i++) pthread_create(&t[i], NULL, stay_alive, NULL);
    
    while(1) sleep(1); // Keep main thread active
    return 0;
}


//ps -T -p <PID_FROM_PROGRAM_OUTPUT> ON A NEW COMMAND PROMPT