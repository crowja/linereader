#include <stdlib.h>
#include <stdio.h>
#include "linereader.h"

int
main(void)
{
   struct linereader *z = linereader_new(NULL);
   printf("t/test01\t%s\n", linereader_version());
   linereader_free(&z);
   return 0;
}
