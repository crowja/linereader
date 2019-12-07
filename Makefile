SHELL = /bin/sh

GCC_STRICT_FLAGS = -pedantic -ansi -W -Wall -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -O2
GCC_SANITIZE_FLAGS = -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
CPPFLAGS = -I.
CFLAGS = $(GCC_STRICT_FLAGS)
LDFLAGS =
OTHER_SOURCE = varstr.c
OTHER_INCLUDE = -I.
INDENT_FLAGS = 

.PHONY: check vcheck scheck indent stamp clean

TESTS = t/test01 t/test02 t/test03

linereader.o: linereader.c linereader.h
	$(CC) -c $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) -o $@ linereader.c

check:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC)    $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c linereader.c $(LDFLAGS) ) \
	  && ( t/a.out < t1.ikv ); \
	done 

vcheck:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c linereader.c $(LDFLAGS) ) \
	  && ( valgrind t/a.out < t1.ikv ); \
	done 

scheck:
	@for i in $(TESTS); \
	do \
	  echo "--------------------"; \
	  echo "Running test $$i"; \
	  ( $(CC) -g $(CPPFLAGS) $(OTHER_INCLUDE) $(CFLAGS) $(GCC_SANITIZE_FLAGS) $(OTHER_SOURCE) \
		-o t/a.out $$i.c linereader.c $(LDFLAGS) ) \
	  && ( t/a.out < t1.ikv ); \
	done 

indent: stamp
	@indent $(INDENT_FLAGS) linereader.c
	@indent $(INDENT_FLAGS) linereader.h
	@for i in $(TESTS); \
	do \
	  indent $(INDENT_FLAGS) $$i.c; \
	done 

stamp:
	@bash stamper.bash linereader.c
	@bash stamper.bash linereader.h

clean:
	@/bin/rm -f linereader.o *.o *~ *.BAK *.bak core.* a.out
	@/bin/rm -f t/*.o t/*~ t/*.BAK t/*.bak t/core.* t/a.out

