# Operating Systems Project: Thread Synchronization Techniques in C
This project showcases various thread synchronization techniques in C using mutex, semaphore, and monitor (condition variables). Thread synchronization is critical in multi-threaded applications to ensure that shared resources are accessed safely, preventing race conditions and maintaining data consistency.

# Key Features:
Mutex Example: Demonstrates mutual exclusion using pthread_mutex_t, where threads are locked out of the critical section until the lock is released by the thread currently holding it.
Semaphore Example: Implements a binary semaphore using sem_t to control access to the critical section, ensuring that only one thread enters at a time.
Monitor Example: Implements a monitor using pthread_cond_t and pthread_mutex_t, allowing for conditional synchronization where threads can wait for certain conditions before proceeding.
How it Works:
Each thread attempts to enter a critical section where shared resources would typically be modified.
The critical section is protected by either a mutex, semaphore, or monitor, ensuring safe access by synchronizing thread entry.
This project simulates a realistic multi-threaded environment by creating 5 threads, each showcasing the behavior of the respective synchronization mechanism.
Technologies Used:
POSIX Threads (pthread)
Mutex Locks
Semaphores
Condition Variables (Monitors)
Example Output:
The project demonstrates how different synchronization mechanisms manage concurrent thread access to a critical section by locking, waiting, or signaling threads.

# Compilation & Execution:
To compile and run the program, use the following commands:
# gcc -pthread -o sync_project sync_project.c
# ./sync_project
# Usage:
The program runs three examples sequentially, showing the usage of mutex, semaphore, and monitor for synchronizing thread access.

⚠️ Note: This project is designed for educational purposes to understand the basic concepts of thread synchronization in operating systems.


![image](https://github.com/user-attachments/assets/e4637ff5-8366-41dd-b8d0-02a368f0be35)


