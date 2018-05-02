#include "types.h"
#include "user.h"

int stdout = 1;
int stderr = 2;

int
main(int argc, char *argv[])
{
  //struct rtcdate r;

  /*if (date(&r)) {
    printf(stderr, "Erro na chamada de sistema\n");
    exit();
  }*/

	char *physical = "";

	printf(stdout,"%s\n",(char*)(virt2real(physical)));

  // Imprima a data aqui

  exit();
}