
struct sem {
   struct spinlock lock;
   int value;
   int init;
};

#define NSEM (10)

// Initialises semaphore subsystem - is called from kernel's main()
// during initialisation
void seminit();

// Opens (initialises) specified semaphore.
//
// returns 0 if specified semaphore has been successfully initialised
// returns 1 if the semafore has already been initialised, in which case this call has no effect
// returns -1 if the sem_id is outside of the allowed range (0<= sem_id < NSEM)
int sem_open(int sem_id, unsigned int val);

// Performs V operation (increments the value of the semaphore specified as sem_id by val and then
// wakes up any processes that might be sleeping on that semaphore).
//
// returns 0 if operation is successfully completed 
// returns -1 if the sem_id is outside of allowed range 0<= sem_id < NSEM
// or if the specified semaphore has not been initialised
int sem_post(int sem_id, unsigned int val);


// Performs P operation (decrements the value of the semaphore specified by sem_id by val and puts the calling 
// process to sleep, if the value of the semaphore is < val).
//
// returns 0 if operation is successfully completed
// returns -1 if the sem_id is outside of allowed range 0<= sem_id < NSEM
// or if the specified semaphore has not been initialised.
int sem_wait(int sem_id, unsigned int val); 

// Closes (deinitialises) specified semaphore and wakes up any processes that might be sleeping on it. Note
// that sem_wait() will fail for all processes still sleeping on the semaphore when sem_close() is called, 
// because the semaphore is no longer initialised.
//
// returns 0 if operation is successfully completed
// returns -1 if the sem_id is outside of allowed range 0<= sem_id < NSEM
// or if the specified semaphore has not been initialised.
int sem_close(int sem_id);
