# Philosophers
<h3 align="left">Philosophers:</h3>

![PHILOSOPHERS](https://github.com/ayogun/42-project-badges/blob/main/covers/cover-philosophers-bonus.png)


# Mandatory Part:

Each philosopher is a thread, and they share the same memory space. In the main process, use pthread_create in a loop to create n philosopher threads (n is the first input parameter). Each philosopher thread's task is to repeatedly go through the operations of picking up forks, eating, sleeping, and thinking, while also checking if the philosopher has eaten the required number of times and whether all philosopher threads have done so.

They operate simultaneously. My scheduling strategy is to have even-numbered philosopher threads sleep for one-tenth of the eating time (the third input parameter) first, while odd-numbered philosopher threads first attempt to pick up their left and right forks to eat. At the same time, within each philosopher thread, a corresponding monitor thread is created to monitor the philosopher thread.

Each monitor thread's task is to monitor whether its corresponding philosopher thread has died. It checks every death time + 1 millisecond (the death time is the second input parameter). Although each philosopher's last meal time (t_lastmeal) is a unique variable for that philosopher's thread, for potential future scalability, I use two mutex locks, m_stop and m_eat, in the is_dead function to ensure exclusive modification of the shared stop variable when the conditions are met, marking the philosopher thread as dead. Typically, pthread_mutex_lock and pthread_mutex_unlock are used in pairs.

Similarly, when a philosopher thread picks up the left and right forks, mutex locks fork_l and fork_r are used to prevent resource contention. If the input number of philosophers is 1, that philosopher thread sleeps for twice the death time, the monitor thread detects the death state, marks it as dead, and the philosopher thread ends. If the number of philosophers is greater than 1, the philosopher thread also checks whether it has eaten the required number of times (possibly the fifth input parameter). If it has, the count of philosopher threads that have eaten enough (meta_shared->n_p_eat_fl) increases by 1. Then, it checks whether all philosopher threads have eaten enough. This variable is in shared resources, so a mutex lock m_stop is used before accessing or modifying it, and immediately unlocked afterward. Once it is found that all philosopher threads have eaten enough, it marks death and ends the philosopher thread.

Similarly, when printing output information, a mutex lock is used to ensure that threads do not compete for print resources, avoiding output confusion.

Returning to the main process, pthread_join is called to wait for each philosopher thread to finish, reclaim resources, and finally pthread_mutex_destroy is called to destroy all mutex locks.

# Parte Obligatoria:

Cada filósofo es un hilo, y todos comparten el mismo espacio de memoria. En el proceso principal, se utiliza pthread_create en un bucle para crear n hilos de filósofos (n es el primer parámetro de entrada). La tarea de cada hilo de filósofo es realizar repetidamente las operaciones de tomar los tenedores, comer, dormir y pensar, además de verificar si el filósofo ha comido el número requerido de veces y si todos los hilos de filósofos han hecho lo mismo.

Todos ellos operan simultáneamente. Mi estrategia de planificación es hacer que los hilos de filósofos con números pares duerman primero una décima parte del tiempo de comer (el tercer parámetro de entrada), mientras que los hilos de filósofos con números impares intentan primero tomar sus tenedores izquierdo y derecho para comer. Al mismo tiempo, dentro de cada hilo de filósofo, se crea un hilo monitor correspondiente para supervisar el hilo del filósofo.

La tarea de cada hilo monitor es verificar si su hilo de filósofo correspondiente ha muerto. Este verifica cada tiempo de muerte + 1 milisegundo (el tiempo de muerte es el segundo parámetro de entrada). Aunque el tiempo de la última comida de cada filósofo (t_lastmeal) es una variable única para el hilo de ese filósofo, para la posible escalabilidad futura, utilizo dos bloqueos mutuos, m_stop y m_eat, en la función is_dead para garantizar la modificación exclusiva de la variable compartida stop cuando se cumplan las condiciones, marcando el hilo del filósofo como muerto. Normalmente, pthread_mutex_lock y pthread_mutex_unlock se utilizan en pares.

De manera similar, cuando un hilo de filósofo toma los tenedores izquierdo y derecho, se utilizan bloqueos mutuos fork_l y fork_r para evitar la contención de recursos. Si el número de filósofos es 1, ese hilo de filósofo duerme por el doble del tiempo de muerte, el hilo monitor detecta el estado de muerte, lo marca como muerto y el hilo del filósofo termina. Si el número de filósofos es mayor que 1, el hilo del filósofo también verifica si ha comido el número requerido de veces (posiblemente el quinto parámetro de entrada). Si lo ha hecho, el conteo de hilos de filósofos que han comido lo suficiente (meta_shared->n_p_eat_fl) aumenta en 1. Luego, verifica si todos los hilos de filósofos han comido lo suficiente. Esta variable está en recursos compartidos, por lo que se utiliza un bloqueo mutuo m_stop antes de acceder o modificarla, y se desbloquea inmediatamente después. Una vez que se descubre que todos los hilos de filósofos han comido lo suficiente, se marca la muerte y se termina el hilo del filósofo.

De manera similar, cuando se imprime la información de salida, se utiliza un bloqueo mutuo para garantizar que los hilos no compitan por los recursos de impresión, evitando confusiones en la salida.

Volviendo al proceso principal, se llama a pthread_join para esperar a que cada hilo de filósofo termine, recuperar los recursos y, finalmente, se llama a pthread_mutex_destroy para destruir todos los bloqueos mutuos.

# BONUS Part:

Each philosopher is an independent process, and they occupy their own separate memory space. Multiple processes access and modify shared data using semaphores. In the main process, the fork function is called in a loop to create philosopher processes. When the returned process ID is 0, it enters the philosopher process.

The task of the philosopher process is to repeatedly perform the operations of picking up forks, eating, sleeping, and thinking, and to check whether the philosopher has eaten the required number of times and whether all philosopher processes have done so.

Within each philosopher process, a corresponding monitor thread is created to monitor the death status of the philosopher process, also checking every t_death + 1 millisecond. These monitor threads and all philosopher processes run simultaneously. In the philosopher process, even-numbered philosopher processes sleep for one-tenth of the eating time, while odd-numbered philosopher processes pick up the forks first. Semaphores are used to control access and ensure no data race occurs. sem_wait increases the semaphore's value by 1, while sem_post decreases it by 1. When the semaphore value is 0, the process that wants to acquire the semaphore gets blocked, waiting for the semaphore's value to be greater than 0 before proceeding with subsequent operations.

Since each process has its own independent memory space, the overhead of context switching is higher compared to threads. Additionally, processes frequently need to enter kernel mode for synchronization and communication operations, whereas threads only use mutexes and other synchronization methods in user mode. Thus, inter-process communication (IPC) mechanisms are more complex and slower than communication between threads. In certain systems and situations, this may result in multiple philosopher processes dying without timely communication to terminate the process, causing delays.

# Parte BONUS:

Cada filósofo es un proceso independiente y ocupan su propio espacio de memoria separado. Varios procesos acceden y modifican los datos compartidos utilizando semáforos. En el proceso principal, se llama a la función fork en un bucle para crear procesos de filósofos. Cuando el ID del proceso devuelto es 0, se ingresa al proceso del filósofo.

La tarea del proceso del filósofo es realizar repetidamente las operaciones de tomar los tenedores, comer, dormir y pensar, además de verificar si el filósofo ha comido el número requerido de veces y si todos los procesos de filósofos lo han hecho.

Dentro de cada proceso de filósofo, se crea un hilo de monitor correspondiente para supervisar el estado de muerte del proceso del filósofo, también verificando cada tiempo de muerte + 1 milisegundo. Estos hilos de monitor y todos los procesos de filósofos se ejecutan simultáneamente. En el proceso del filósofo, los procesos de filósofos con números pares duermen durante una décima parte del tiempo de comer, mientras que los procesos de filósofos con números impares toman los tenedores primero. Se utilizan semáforos para controlar el acceso y asegurar que no ocurra una carrera de datos. sem_wait aumenta el valor del semáforo en 1, mientras que sem_post lo disminuye en 1. Cuando el valor del semáforo es 0, el proceso que quiere adquirir el semáforo se bloquea, esperando a que el valor del semáforo sea mayor que 0 antes de continuar con las operaciones posteriores.

Dado que cada proceso tiene su propio espacio de memoria independiente, el cambio de contexto tiene un costo mayor en comparación con los hilos. Además, los procesos necesitan entrar frecuentemente en modo kernel para las operaciones de sincronización y comunicación, mientras que los hilos solo usan mutexes y otros métodos de sincronización en modo usuario. Por lo tanto, los mecanismos de comunicación entre procesos (IPC) son más complejos y lentos que la comunicación entre hilos. En ciertos sistemas y situaciones, esto puede resultar en que varios procesos de filósofos mueran sin una comunicación oportuna para terminar el proceso, causando retrasos.

