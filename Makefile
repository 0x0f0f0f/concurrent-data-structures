CC = clang
CFLAGS = -Wall -pedantic -fPIE -std=gnu99
OPTFLAGS = -O3
INCLUDES = -I.
LOGLEVEL = -DLOG_LVL=LOG_LVL_NOTICE

NAME=util

.PHONY: all bin clean debug
.SUFFIXES: .c .h

OBJECTS =  buf.o linked_list.o hash_table.o lqueue.o conc_buf.o conc_lqueue.o

default: static

static: obj
	ar rcs util.a $(OBJECTS)

# dynamic library
dynamic: CFLAGS+=-fPIC
dynamic: obj
	$(CC) -shared $(OBJECTS) -o lib$(NAME).so

obj: $(OBJECTS)

%.o: %.c %.h
	$(CC) $(CFLAGS) $(LOGLEVEL) $(OPTFLAGS) $(INCLUDES) $(LIBS)  -c -o $@ $<

sanitize: CFLAGS+=-fno-omit-frame-pointer -fsanitize=thread
sanitize: debug

debug: CFLAGS+=-g
debug: all

clean:
	$(RM) -f *.o
