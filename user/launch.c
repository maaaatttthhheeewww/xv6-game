#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 2)
  {
     printf("Usage: launch cmd arg1 arg2 arg3 ...\n");
     exit(0);
  }
  if (fork() == 0)
  {
     exec(argv[1],&argv[1]); 
  }
  wait(0);
  exit(0);
  return 0;
}
