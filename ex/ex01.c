#include <stdlib.h>
#include <stdio.h>
#include "linereader.h"

int
main(void)
{
   /* NULL specifies stdin */
   struct linereader *z = linereader_new(NULL);
   char       *line;

   while ((line = (char *) linereader_next(z)))
      printf("%s", line);

   linereader_free(&z);

   return 0;
}
