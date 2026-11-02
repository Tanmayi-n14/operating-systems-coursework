# Level 2: Orange Projects & Advanced Problem Sets

This directory documents the Level 2 advanced assignments and projects completed for the Operating Systems course.

---

## 1. Orange Problem 2: Clash Arena Concurrency & Battle Simulation
* **Directory**: [`Orange-Problem-2-Clash-Arena-IPC/`](./Orange-Problem-2-Clash-Arena-IPC)
* **Problem**: Multi-threaded arena battle simulation simulating dynamic troop deployments, elixir consumption, and shared arena state synchronization.
* **Key Mechanisms**:
  * POSIX Threads (`pthread_create`, `pthread_join`) for parallel troop deployment.
  * Mutexes (`pthread_mutex_t arena_mutex`, `pthread_mutex_t elixir_lock`) ensuring thread-safe access to arena state and elixir pool.
  * Counting Semaphores (`sem_t arena_empty_slots`) for capacity enforcement.
  * Anonymous Pipes (`battle_log_pipe[2]`) for inter-process logging.
* **Source Files**:
  * `PES1UG24CS493.c`: Student implementation with dynamic SRN-based battle rules and synchronization.
  * `clash_server.c`: Course server harness.
  * `OS-Orange.pdf`: Formal assignment problem statement.

---

## 2. Orange Project 3/4: PES-VCS (Custom Version Control System in C)
* **Dedicated Repository**: [**Tanmayi-n14 / PES1UG24CS493-pes-vcs**](https://github.com/Tanmayi-n14/PES1UG24CS493-pes-vcs)
* **Description**: A full-fledged Git-compatible version control system written from scratch in pure C.
* **Implemented Capabilities**:
  * **Phase 1: Object Store** — Content-addressable SHA-256 storage (`.pes/objects/`) for blobs, commits, and trees.
  * **Phase 2: Tree Objects** — Hierarchical directory representation and binary serialization.
  * **Phase 3: The Index** — Staging area with binary index parsing and status diffing.
  * **Phase 4: Commits & References** — Commit objects, metadata, parent chains, and `.pes/HEAD` tracking.
  * **Phase 5 & 6 Analysis**: Mark-and-sweep garbage collection algorithms, dirty-tree conflict detection, and detached HEAD recovery.
