# linereader 1.0.0-dev0.
C scrap for reading a file line by line.

## Snippet

```c
#include "linereader.h"
/* Data from stdin */
struct linereader *z = linereader_new(NULL);
char *line;
      
while ((line = linereader_next(z)))
   printf("%s", line);
   . . .

linereader_free(&z);
```

## What you need
