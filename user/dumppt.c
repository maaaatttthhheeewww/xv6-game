#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if (argc < 2)
  {
     printf("Usage: dumppt pid\n");
     exit(0);
  }
  dumppt(atoi(argv[1]));
  exit(0);
  return 0;
}
