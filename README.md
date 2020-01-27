# linereader 1.1.0-dev0.

C-scrap for reading a file line by line. If built with
[Zlib support](https://www.zlib.net/) (-DHAVE\_ZLIB), which is
completely optional, the input file/stream can be Zlib compressed,
e.g. gzipped files.

## Here's how you use it

```c
#include <stdlib.h>
#include <stdio.h>
#include "linereader.h"

int main(void)
{
   /* NULL specifies stdin */
   struct linereader *z = linereader_new(NULL);
   char *line;

   while ((line = (char *) linereader_next(z)))
      printf("%s", line);

   linereader_free(&z);

   return 0;
}
```

## What you need

All you need is:

* linereader.c and linereader.h.
* varstr.c and varstr.h from [crowja/varstr](https://github.com/crowja/varstr).
