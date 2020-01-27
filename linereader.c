/**
 *  @file linereader.c
 *  @version 1.1.0-dev0
 *  @date Sun Jan 26 19:28:47 CST 2020
 *  @copyright 2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

/* Needed because fileno() seems to be POSIX C but not ANSI C */
#define _POSIX_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "varstr.h"
#ifdef   HAVE_ZLIB
#include "zlib.h"
#else
/* Zlib is not available, define macros mimicking some of the gz* funcs */
typedef FILE *gzFile;
#define  gzdopen(a, b)    fdopen((a), (b))
#define  gzopen(a, b)     fopen((a), (b))
#define  gzclose(a)       fclose((a))
#define  gzgetc(a)        getc((a))
#define  gzgets(a, b, c)  fgets((b), (c), (a))
/* a=file, b=buf, c=len */
#endif
#include "linereader.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

#ifdef  _BUFSIZE
#undef  _BUFSIZE
#endif
#define _BUFSIZE      1024                       /* _BUFSIZE > 1 */

struct linereader {
   gzFile      in;
   char        buf[_BUFSIZE];
   struct varstr *text;
   /**
    *  Flag if test for compressed input has been completed. The first chunk of
    *  input is examined and an error is reported if it looks to be compressed
    *  and Zlib support is not available.
    */
   int         checked;
   int         at_start;
};

struct linereader *
linereader_new(char *fname)
{
   struct linereader *tp;
   char       *tmp;
   unsigned char bytes[3];

   tp = (struct linereader *) malloc(sizeof(struct linereader));
   if (_IS_NULL(tp))
      return NULL;

   if (_IS_NULL(fname))
      tp->in = gzdopen(fileno(stdin), "r");
   else
      tp->in = gzopen(fname, "r");
   if (_IS_NULL(tp->in))
      return NULL;

#ifdef  HAVE_ZLIB
   gzbuffer(tp->in, 1024 * 32);
#endif

   tp->text = varstr_new();

   /**
    *  Peek at the first two bytes. If the data stream is Zlib compressed its
    *  first two bytes will be 0x1f and 0x8b. If HAVE_ZLIB, these will be
    *  interpreted by gzgets and handled appropriately and won't show up. This
    *  is simply checking to see if the input stream is compressed but that
    *  linereader was compiled without Zlib support.
    */

   tmp = gzgets(tp->in, (char *) bytes, 3);      /* try reading two bytes */

   if (_IS_NULL(tmp)) {                          /* eof */
      /* that's okay, pass */
   }
   else if (strlen(tmp) < 2) {                   /* read one byte at most */
      /* that's okay, append bytes to tp->text */
      varstr_cat(tp->text, (char *) bytes);
   }
   else if (bytes[0] != 0x1f || bytes[1] != 0x8b) {     /* not Zlib data */
      /* that's okay, append bytes to tp->text */
      varstr_cat(tp->text, (char *) bytes);
   }
   else {                                        /* compressed data, probably missing Zlib support */
      /* clean up and return NULL */
      linereader_free(&tp);
      return NULL;
   }

   tp->at_start = 1;

   return tp;
}

void
linereader_free(struct linereader **pp)
{
   if (_IS_NULL(*pp))
      return;

   varstr_free(&(*pp)->text);

   if (!_IS_NULL((*pp)->in))
      gzclose((*pp)->in);

   _FREE(*pp);
   *pp = NULL;
}

const char *
linereader_version(void)
{
   return "1.1.0-dev0";
}

const char *
linereader_next(struct linereader *p)
{
   /* Skip empty on first call since p->text will have 1-3 bytes set by constructor */
   if (p->at_start)
      p->at_start = 0;
   else
      varstr_empty(p->text);

   for (;;) {                                    /* loop to consume a single line */

      if (NULL == gzgets(p->in, p->buf, _BUFSIZE)) {

         if (strlen(varstr_str(p->text)) == 0)   /* eof and no text accumulated -- done! */
            return NULL;
         else
            break;
      }

      varstr_cat(p->text, p->buf);

      if (NULL != strchr(p->buf, '\n'))
         break;
   }

   return (const char *) varstr_str(p->text);
}

#undef  _IS_NULL
#undef  _FREE
#undef  _BUFSIZE
