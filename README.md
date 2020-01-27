# linereader 1.0.0-dev0.
123456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
C-scrap for reading a file line by line. If built with Zlib support
(-DHAVE\_ZLIB) the input file/stream can be Zlib compressed, e.g. gzipped files.

## Here's how you use it

```c
#include "linereader.h"
. . .

/* Data is from stdin */
struct linereader *z = linereader_new(NULL);
char *line;
      
while ((line = linereader_next(z))) {
   printf("%s", line);
   . . .
}

linereader_free(&z);
```

## What you need

* linereader.c and linereader.h.
* [varstr.c and varstr.h from](https://github.com/crowja/varstr).
