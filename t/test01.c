#include <stdlib.h>
#include <stdio.h>
#include "linereader.h"

int
main(int argc, char *argv[])
{
   struct linereader *z = linereader_new();
   printf("t/test01\t%s\n", linereader_version());
   linereader_free(z);
   return 0;
}
