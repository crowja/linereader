#include <stdlib.h>
#include <stdio.h>
#include "linereader.h"

int
main(int argc, char *argv[])
{
   struct linereader *z = linereader_new();
   const char *cp;

   printf("t/test02\t%s\n", linereader_version());
   printf("linereader version = %s\n", linereader_version());

#if 1
   linereader_init(z, "linereader.c");
#endif

   for (;;) {
      cp = linereader_next(z);

      if (NULL == cp)
         break;

      else
         printf("->%s", cp);
   }

   linereader_free(z);

   return 0;
}
