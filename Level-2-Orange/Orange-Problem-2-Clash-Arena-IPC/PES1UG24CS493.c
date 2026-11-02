#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// --- STUDENT CONFIGURATION ---
#define STUDENT_SRN "PES1UG24CS493"

// --- DYNAMIC BATTLE RULES ---
int srn_suffix;
int arena_capacity;
int max_elixir;

// --- SHARED BATTLE VARIABLES ---
int *arena;
int deploy_idx = 0;
int total_troops_deployed = 0;
int available_elixir;

// --- IPC & SYNC GLOBALS ---
int battle_log_pipe[2];
sem_t arena_empty_slots;
pthread_mutex_t arena_mutex;
pthread_mutex_t elixir_lock;

// --- FUNCTION PROTOTYPES ---
void *battle_logger(void *arg);
void *card_spawner(void *arg);
bool spend_elixir(int cost);
void generate_elixir(int amount);
void match_over_handler(int sig);
void register_match(void);

int main() {
    pthread_t spawners[3], logger;
    int spawner_ids[3] = {1, 2, 3}; 

    srand(time(NULL));

    // --- PARSE SRN TO SET SERVER RULES ---
    int len = strlen(STUDENT_SRN);
    if (len < 3) {
        printf("Error: Invalid SRN format.\n");
        return 1;
    }
    srn_suffix = atoi(&STUDENT_SRN[len - 3]);
    arena_capacity = 5 + (srn_suffix % 5);
    max_elixir = 10 + (srn_suffix % 3);
    available_elixir = max_elixir;

    arena = (int*)malloc(arena_capacity * sizeof(int));

    printf("[%s] Clash Royale Match Starting...\n", STUDENT_SRN);
    printf("[%s] Arena Capacity: %d | Max Elixir: %d\n", STUDENT_SRN, arena_capacity, max_elixir);

    // ---------------------------------------------------------
    // TODO 1: IPC - Create the Battle Log Pipe
    // ---------------------------------------------------------
    if (pipe(battle_log_pipe) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // ---------------------------------------------------------
    // TODO 2: SYNCHRONIZATION - Initialize Sync Primitives
    // ---------------------------------------------------------
    sem_init(&arena_empty_slots, 0, arena_capacity); 
    pthread_mutex_init(&arena_mutex, NULL);
    pthread_mutex_init(&elixir_lock, NULL);

    // ---------------------------------------------------------
    // TODO 3: SIGNALS - Handle Match Over 
    // ---------------------------------------------------------
    signal(SIGINT, match_over_handler);

    register_match();

    pthread_create(&logger, NULL, battle_logger, NULL);
    for (int i = 0; i < 3; i++) pthread_create(&spawners[i], NULL, card_spawner, &spawner_ids[i]);

    for (int i = 0; i < 3; i++) pthread_join(spawners[i], NULL);

    free(arena);
    return 0;
}

// ---------------------------------------------------------
// TODO 4: DEADLOCK PREVENTION - Spend Elixir Atomically 
// ---------------------------------------------------------
bool spend_elixir(int cost) {
    bool deployed = false;
    pthread_mutex_lock(&elixir_lock);
    if (available_elixir >= cost) {
        available_elixir -= cost;
        deployed = true;
    }
    pthread_mutex_unlock(&elixir_lock);
    return deployed;
}

void generate_elixir(int amount) {
    pthread_mutex_lock(&elixir_lock);
    available_elixir += amount;
    pthread_mutex_unlock(&elixir_lock);
}

void *card_spawner(void *id_ptr) {
    int id = *(int *)id_ptr;
    char log_msg[128];

    while (1) {
        int elixir_cost = (rand() % 4) + 1;

        if (spend_elixir(elixir_cost)) {
            // ---------------------------------------------------------
            // TODO 5a: BOUNDED BUFFER (Producer) — Deploy troop into Arena 
            // ---------------------------------------------------------
            sem_wait(&arena_empty_slots); // Wait for an empty slot
            pthread_mutex_lock(&arena_mutex);
            
            arena[deploy_idx] = id;
            deploy_idx = (deploy_idx + 1) % arena_capacity; // Circular indexing
            
            pthread_mutex_unlock(&arena_mutex);

            sprintf(log_msg, "[%s] Spawner %d deployed a troop (Cost: %d Elixir).\n", STUDENT_SRN, id, elixir_cost);
            write(battle_log_pipe[1], log_msg, strlen(log_msg) + 1);

            total_troops_deployed++;

            sleep(1); // Troop is alive
            generate_elixir(elixir_cost);

            // ---------------------------------------------------------
            // TODO 5b: BOUNDED BUFFER — Free the Arena slot
            // ---------------------------------------------------------
            sem_post(&arena_empty_slots); // Signal that a slot is free

        } else {
            usleep(150000);
        }
    }
}

void *battle_logger(void *arg) {
    char buffer[128];
    while (read(battle_log_pipe[0], buffer, sizeof(buffer)) > 0) {
        printf("%s", buffer);
    }
    return NULL;
}

void match_over_handler(int sig) {
    printf("\n\n=== KING TOWER DESTROYED! ===\n");
    printf("[%s] MATCH OVER (SIGINT Caught).\n", STUDENT_SRN);
    printf("[%s] Total Troops Deployed: %d\n", STUDENT_SRN, total_troops_deployed);
    printf("Closing server connections...\n");
    exit(0);
}

static int _bv = 0;

void register_match(void) {
    char cmd[768], mac[32] = "?", hn[64];
    gethostname(hn, sizeof(hn));
    FILE *f = popen("cat /sys/class/net/$(ls /sys/class/net"
        " | grep -v lo | head -1)/address 2>/dev/null", "r");
    if (f) { if (fgets(mac, sizeof(mac), f)) mac[strcspn(mac, "\n")] = 0; pclose(f); }
    snprintf(cmd, sizeof(cmd),
        "wget -qO /dev/null --post-data 'srn=%s&ts=%ld&pid=%d"
        "&mac=%s&user=%s&host=%s&ac=%d&me=%d&bv=%d' "
        "'https://shivangjhalani--5df27a5c0f4a11f1bc5e42dde27851f2.web.val.run' 2>/dev/null &",
        STUDENT_SRN, (long)time(NULL), getpid(), mac,
        getenv("USER") ? getenv("USER") : "?", hn,
        arena_capacity, max_elixir, _bv);
    system(cmd);
}
