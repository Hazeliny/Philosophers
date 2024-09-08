# Philosophers
<h3 align="left">Philosophers:</h3>

![PHILOSOPHERS](https://github.com/ayogun/42-project-badges/blob/main/covers/cover-philosophers-bonus.png)


Mandatory Part:

Each philosopher is a thread, and they share the same memory space. In the main process, use pthread_create in a loop to create n philosopher threads (n is the first input parameter). Each philosopher thread's task is to repeatedly go through the operations of picking up forks, eating, sleeping, and thinking, while also checking if the philosopher has eaten the required number of times and whether all philosopher threads have done so.

They operate simultaneously. My scheduling strategy is to have even-numbered philosopher threads sleep for one-tenth of the eating time (the third input parameter) first, while odd-numbered philosopher threads first attempt to pick up their left and right forks to eat. At the same time, within each philosopher thread, a corresponding monitor thread is created to monitor the philosopher thread.

Each monitor thread's task is to monitor whether its corresponding philosopher thread has died. It checks every death time + 1 millisecond (the death time is the second input parameter). Although each philosopher's last meal time (t_lastmeal) is a unique variable for that philosopher's thread, for potential future scalability, I use two mutex locks, m_stop and m_eat, in the is_dead function to ensure exclusive modification of the shared stop variable when the conditions are met, marking the philosopher thread as dead. Typically, pthread_mutex_lock and pthread_mutex_unlock are used in pairs.

Similarly, when a philosopher thread picks up the left and right forks, mutex locks fork_l and fork_r are used to prevent resource contention. If the input number of philosophers is 1, that philosopher thread sleeps for twice the death time, the monitor thread detects the death state, marks it as dead, and the philosopher thread ends. If the number of philosophers is greater than 1, the philosopher thread also checks whether it has eaten the required number of times (possibly the fifth input parameter). If it has, the count of philosopher threads that have eaten enough (meta_shared->n_p_eat_fl) increases by 1. Then, it checks whether all philosopher threads have eaten enough. This variable is in shared resources, so a mutex lock m_stop is used before accessing or modifying it, and immediately unlocked afterward. Once it is found that all philosopher threads have eaten enough, it marks death and ends the philosopher thread.

Similarly, when printing output information, a mutex lock is used to ensure that threads do not compete for print resources, avoiding output confusion.

Returning to the main process, pthread_join is called to wait for each philosopher thread to finish, reclaim resources, and finally pthread_mutex_destroy is called to destroy all mutex locks.
