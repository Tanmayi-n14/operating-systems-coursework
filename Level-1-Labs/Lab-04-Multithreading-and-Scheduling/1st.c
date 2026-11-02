#include <stdio.h>
#include <pthread.h>

int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int sums[4] = {0}; // Each thread stores its result here

void* sum_array(void* arg) {
    int id = *(int*)arg;
    int start = id * 2;       // Simple division for 10 elements
    int end = (id == 3) ? 10 : (id + 1) * 2; 

    for (int i = start; i < end; i++) sums[id] += arr[i];
    return NULL;
}

int main() {
    pthread_t threads[4];
    int ids[4] = {0, 1, 2, 3};

    for (int i = 0; i < 4; i++) pthread_create(&threads[i], NULL, sum_array, &ids[i]);
    for (int i = 0; i < 4; i++) pthread_join(threads[i], NULL);

    int total = 0;
    for (int i = 0; i < 4; i++) total += sums[i];
    printf("Total Sum: %d\n", total);
    return 0;
}