#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_sem_open(void)
{
  int sem_id;
  int sem_val;
  argint(0, &sem_id);
  argint(1, &sem_val);
  return sem_open(sem_id,(unsigned int)sem_val); 
}

uint64
sys_sem_post(void)
{
  int sem_id;
  int sem_val;
  argint(0, &sem_id);
  argint(1, &sem_val);
  return sem_post(sem_id,(unsigned int)sem_val); 
}

uint64
sys_sem_wait(void)
{
  int sem_id;
  int sem_val;
  argint(0, &sem_id);
  argint(1, &sem_val);
  return sem_wait(sem_id,(unsigned int)sem_val); 
}

uint64
sys_sem_close(void)
{
  int sem_id;
  argint(0, &sem_id);
  return sem_close(sem_id);
}

