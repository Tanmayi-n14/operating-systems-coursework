#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_work(void* arg) {
    int* status = malloc(sizeof(int));
    *status = 42; // This is the "exit status"
    pthread_exit((void*)status);
}

int main() {
    pthread_t thread;
    void* exit_val;

    pthread_create(&thread, NULL, thread_work, NULL);
    pthread_join(thread, &exit_val); // Captures the status

    printf("Thread exited with status: %d\n", *(int*)exit_val);
    free(exit_val);
    return 0;
}