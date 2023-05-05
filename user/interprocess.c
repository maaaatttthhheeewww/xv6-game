#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/memlayout.h"
#include "user/user.h"

/* Assignment 5, question 3  
 *
 * Modify this program to prevent race conditions. Use semaphore system calls.
 * Semaphore system calls are defined in user/user.h and implemented in kernel/sem.c. 
 * Please refer to example programs and lecture notes posted on Brightspace for more detail.
 *
 * This program is a bare-bones example of the thread pool design pattern, which is 
 * also called "replicated workers pattern" or "thread crew pattern". The idea is that 
 * the application uses a small number of identical "worker" processes for processing a large 
 * array of data items. It works as follows: initially all worker processes are idle. 
 * An idle worker process tries to get the next portion of data from the data array,
 * and - if successful - immediately starts processing it.  If there is no more data
 * to process, the worker process terminates.
 *
 * Function main() initialises the array as follows:
 *
 * a[0]=0
 * a[1]=1
 * a[2]=2
 * a[3]=3
 * a[4]=4
 * a[5]=5
 * a[6]=6
 * a[7]=7
 * a[8]=8
 * a[9]=9
 * 
 * The processing consists in incrementing each item's value by 1 in a loop 100000 times.
 * The correct values *after* processing should be
 *
 * a[0]=100000
 * a[1]=100001
 * a[2]=100002
 * a[3]=100003
 * a[4]=100004
 * a[5]=100005
 * a[6]=100006
 * a[7]=100007
 * a[8]=100008
 * a[9]=100009
 *
 * Please feel free to add/rearrange code and semaphores, as you see fit, to fix this program.
 */
 
// Number of data items in the array
#define N (10)

// Number of worker processes
#define M (3)

struct data {
  int value;
  char processed;
};


struct shared_space {
  struct data a[N];  // array of N items
};

// situate shared_space in the shared virtual memory page
volatile struct shared_space *s = (volatile struct shared_space*) 0x3FFFFFD000;

// Initialise the semaphores
void init_semaphores() {
  sem_open(0, N);
  sem_open(1, N);

}

// This method gets the next piece of data to be processed
int get_item() 
{
   int i;

   // Wait for an available item in the array
   sem_wait(0, N);

   for (i = 0; i < N; i++) 
   {
      if (s->a[i].processed == 0) 
      {
	 // Wait for an available slot in the array
	 sem_wait(1, N);

	 // Mark the item as processed and return its index
s->a[i].processed = 1;
return i;
}
}

// No more data to process
return -1;
}

// This method processes a single data item
void process_item(int index)
{
int i;

// Increment the value of the item 100000 times
for (i = 0; i < 100000; i++)
{
s->a[index].value++;
}

// Release the slot in the array
sem_post(1, N);

}

// This is the worker process
void worker_process()
{
int index;

while (1)
{
// Get the next item to process
index = get_item();
if (index < 0) 
{
  // No more data to process
  exit(0);
}

// Process the item
process_item(index);

// Release the item in the array
sem_post(0, N);
}
}

int main(int argc, char *argv[])
{
int i, pid;

// Initialise the array
for (i = 0; i < N; i++)
{
s->a[i].value = i;
s->a[i].processed = 0;
}

// Create worker processes
for (i = 0; i < M; i++)
{
if ((pid = fork()) == 0)
{
// This is the worker process
worker_process();
}
}

// Wait for worker processes to finish
for (i = 0; i < M; i++)
{
wait(0);
}

// Print the results
for (i = 0; i < N; i++)
{
printf("a[%d]=%d\n", i, s->a[i].value);
}

exit(0);
}