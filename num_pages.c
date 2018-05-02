#include "types.h"
#include "user.h"

int stdout = 1;
int stderr = 2;

int
main(int argc, char *argv[])
{

  printf(stdout,"%d\n",num_pages());
  exit();
}