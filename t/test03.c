#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linereader.h"

static char *
_chomp(char *str)
{
   unsigned    i = strlen(str);

   while (i > 0) {
      i -= 1;
      if (str[i] == '\n')
         str[i] = '\0';
      else
         break;
   }

   return str;
}


int
main(void)
{
   struct linereader *z = linereader_new(NULL);
   const char *cp;
   char       *fake = NULL;

   printf("t/test03\t%s\n", linereader_version());
   printf("linereader version = %s\n", linereader_version());

   for (;;) {
      cp = linereader_next(z);

      if (NULL == cp)
         break;

      fake = realloc(fake, (1 + strlen(cp)) * sizeof(char));

      _chomp((char *) cp);
      printf("->%s<-\n", cp);
   }

   linereader_free(&z);
   free(fake);

   return 0;
}
