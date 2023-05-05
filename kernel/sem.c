#include "types.h"
#include "riscv.h"
#include "memlayout.h"
#include "defs.h"
#include "spinlock.h"
#include "sem.h"

struct sem sem[NSEM];

// called from kernel's main()
void seminit()
{ 
  for (int i=0; i<NSEM; i++)
  {
     initlock(&sem[i].lock, "sem");
     sem[i].init = 0;
     sem[i].value = 0;
  }
}

// Opens (initialises) specified semaphore.
//
// returns 0 if specified semaphore has been successfully initialised
// returns 1 if the semafore has already been initialised, in which case this call has no effect
// returns -1 if the sem_id is outside of the allowed range (0<= sem_id < NSEM)
int sem_open(int sem_id, unsigned int val) 
{
  int res = -1;	
  struct sem *s;

  if (sem_id >= 0 &&  sem_id < NSEM) 
  {
    s = &sem[sem_id];	  
    acquire(&s->lock);
    if (s -> init != 0) 
    {
       res = 1;
    } 
    else 
    {
       s->value = val;
       s->init = 1;
       res = 0;
    }
    release(&s->lock);
  }
  return res;
}

// Performs V operation (increments the value of the semaphore specified as sem_id by val and then
// wakes up any processes that might be sleeping on that semaphore).
//
// returns 0 if operation is successfully completed
// returns -1 if the sem_id is outside of allowed range 0<= sem_id < NSEM
// or if the specified semaphore has not been initialised
int sem_post(int sem_id, unsigned int val)
{
  int res = -1;
  struct sem *s;

  if (sem_id >= 0 &&  sem_id < NSEM)
  {
    s = &sem[sem_id];
    acquire(&s->lock);
    //printf("sem_post(): sem id = %d, sem value = %d\n val = %d", sem_id, s->value, val);
    if (s->init != 0) 
    {
      s->value += val;
      wakeup(s);
      res = 0;
    }
    release(&s->lock);
  }
  return res;
}
   
// Performs P operation (decrements the value of the semaphore specified by sem_id by val and puts the calling 
// process to sleep, if the value of the semaphore is < val).
//
// returns 0 if operation is successfully completed
// returns -1 if the sem_id is outside of allowed range 0<= sem_id < NSEM
// or if the specified semaphore has not been initialised.
int sem_wait(int sem_id, unsigned int val)
{
  int res = -1;
  struct sem *s;

  if (sem_id >= 0 &&  sem_id < NSEM)
  {
    s = &sem[sem_id];
    acquire(&s->lock);
    if (s->init != 0) 
    {
      //printf("sem_wait(): sem id = %d, sem value = %d\n val = %d", sem_id, s->value, val);
      while ((s->init != 0) && (s->value < val))
      {
        sleep(s,&s->lock);
      }
      if (s->init != 0) 
      {
        s->value -= 1;
        res = 0;
      }
    } 
    release(&s->lock);
  }
  return res;
}
   


// Closes (deinitialises) specified semaphore and wakes up any processes that might be sleeping on it. Note
// that sem_wait() will fail for all processes still sleeping on the semaphore when sem_close() is called,
// because the semaphore is no longer initialised.
//
// returns 0 if operation is successfully completed
// returns -1 if the sem_id is outside of allowed range 0<= sem_id < NSEM
// or if the specified semaphore has not been initialised.
int sem_close(int sem_id)
{
  int res = -1;
  struct sem *s;

  if (sem_id >= 0 &&  sem_id < NSEM)
  {
    s = &sem[sem_id];
    acquire(&s->lock);
    if (s->init != 0)
    {
      s->init = 0;
      wakeup(s);
      res = 0;
    }
    release(&s->lock);
  }
  return res;
}

