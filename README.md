# Operating Systems Coursework & Labs (Semester 4)

Comprehensive collection of system programming, process synchronization, memory management, and Unix internals implemented in C as part of the Operating Systems curriculum (UE22CS252A) at PES University.

---

## 📌 Course Progression Overview

```
Operating Systems Coursework
├── Level 1: Core Labs & Hands-on Sessions (Foundations of Unix Systems)
├── Level 1: Banana Problem Challenges (Concurrency & Memory Management)
├── Level 2: Orange Projects (Advanced Synchronization & System Tools)
└── Level 3: Jackfruit Final Project (Container Runtime & Engine)
```

---

## 📂 Repository Structure

### 🔹 [Level 1: Core Labs](./Level-1-Labs/)
Foundational systems programming exercises exploring POSIX APIs in C:
* **[Lab-02-Process-Lifecycle](./Level-1-Labs/Lab-02-Process-Lifecycle/)**:
  * Process creation with `fork()` and `vfork()`.
  * Process termination dynamics: Orphan processes (adoption by `init`/`systemd`) and Zombie processes (defunct state awaiting parent `wait()`).
  * Process image replacement with `exec` family (`example1.c` through `example4.c`).
* **[Lab-03-IPC-Pipes-and-FIFOs](./Level-1-Labs/Lab-03-IPC-Pipes-and-FIFOs/)**:
  * Anonymous half-duplex pipes (`pipe()`) for parent-child IPC.
  * Named pipes / FIFOs (`mkfifo()`) enabling bidirectional communication between unrelated processes (`fifo_read.c` & `fifo_write.c`).
* **[Lab-04-Multithreading-and-Scheduling](./Level-1-Labs/Lab-04-Multithreading-and-Scheduling/)**:
  * POSIX Threads (`pthread`) creation, argument passing, and parallel execution.
  * Multi-threaded array summation and CPU scheduling simulations (`1st.c` through `4th.c`).
* **[Hands-on-Virtual-Memory](./Level-1-Labs/Hands-on-Virtual-Memory/)**:
  * Virtual memory page replacement simulation in C.
  * Comparative implementation of **FIFO** (First-In, First-Out), **LRU** (Least Recently Used), and **Optimal** page replacement algorithms with reference strings.

---

### 🍌 [Level 1: Banana Problem Sets](./Level-1-Banana/)
Rigorous challenge assignments exploring low-level Unix system constraints:
* **[Unit-01-Concurrency-Hive](./Level-1-Banana/Unit-01-Concurrency-Hive/)**:
  * Program: `hive.c`.
  * Spawns worker larvae (processes periodically allocating dynamic memory blocks) and husks (immediate-exit zombie processes).
  * Analyzes Unix process table exhaustion, memory limits, and signal handling.
  * Includes problem specification, report docs, and verification screenshots.
* **[Unit-03-Virtual-Memory](./Level-1-Banana/Unit-03-Virtual-Memory/)**:
  * Comprehensive memory management study, page fault analysis, and TLB translation verification.
  * Includes report (`PES1UG24CS493_banana problem_U3.pdf`) and 17 Ubuntu terminal execution screenshots.

---

### 🍊 [Level 2: Orange Projects](./Level-2-Orange/)
Advanced multi-threaded synchronization and custom system tool construction:
* **[Orange-Problem-2-Clash-Arena-IPC](./Level-2-Orange/Orange-Problem-2-Clash-Arena-IPC/)**:
  * Multi-threaded arena battle simulator (`PES1UG24CS493.c` & `clash_server.c`).
  * Concurrency control using `pthread_mutex_t`, counting semaphores (`sem_t`), and anonymous IPC pipes.
* **Orange Project 3/4 — PES-VCS (Custom Git in C)**:
  * 🔗 **Dedicated Repository**: [**Tanmayi-n14 / PES1UG24CS493-pes-vcs**](https://github.com/Tanmayi-n14/PES1UG24CS493-pes-vcs)
  * Complete custom implementation of Git internals: content-addressable SHA-256 object store (blobs, trees, commits), index staging area, branch/HEAD reference tracking, and mark-and-sweep garbage collection analysis.

---

### 🍈 Level 3: Jackfruit Final Project
* 🔗 **Dedicated Repository**: [**Tanmayi-n14 / OS-Jackfruit**](https://github.com/Tanmayi-n14/OS-Jackfruit)
* Lightweight container runtime and execution engine in C utilizing Linux namespaces (`clone`, `unshare`), cgroups for CPU/memory quotas, and chroot/pivot_root isolation.

---

## 🛠️ Building & Running

All programs are written in standard C conforming to POSIX standards. Compile using `gcc`:

### 1. Multithreaded Programs (`pthread`)
```bash
gcc -pthread -Wall -Wextra Lab-04-Multithreading-and-Scheduling/1st.c -o thread_sum
./thread_sum
```

### 2. IPC Pipes & FIFOs
```bash
# Compile FIFO reader and writer
gcc Lab-03-IPC-Pipes-and-FIFOs/fifo_read.c -o fifo_read
gcc Lab-03-IPC-Pipes-and-FIFOs/fifo_write.c -o fifo_write

# In terminal 1:
./fifo_read

# In terminal 2:
./fifo_write
```

### 3. Page Replacement Simulations
```bash
gcc Hands-on-Virtual-Memory/demo_lru.c -o lru_sim
./lru_sim
```

---

## 👤 Author

* **Tanmayi Nagabhairava** ([@Tanmayi-n14](https://github.com/Tanmayi-n14)) — `PES1UG24CS493`
* Department of Computer Science & Engineering, PES University
