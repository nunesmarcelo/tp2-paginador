#include "types.h"
#include "user.h"

int stdout = 1;
int stderr = 2;

int
main(int argc, char *argv[])
{

	char *physical = "";

	printf(stdout,"%s\n",(char*)(virt2real(physical)));

	// return (char*)(virt2real(physical));

  exit();
}