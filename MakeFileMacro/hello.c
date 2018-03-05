#include <stdio.h>
#include <stdlib.h>

main()
{
#ifdef p1
  printf("Hello p1\n");
#else
  printf("Hello p2\n");
#endif 
}
