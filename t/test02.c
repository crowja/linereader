#include <stdlib.h>
#include <stdio.h>
#include "linereader.h"

int
main(void)
{
   struct linereader *z = linereader_new(NULL);
   const char *cp;

   printf("t/test02\t%s\n", linereader_version());
   printf("linereader version = %s\n", linereader_version());

   for (;;) {
      cp = linereader_next(z);

      if (NULL == cp)
         break;

      else
         printf("->%s", cp);
   }

   linereader_free(&z);

   return 0;
}
