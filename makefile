# hello
### https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html ###

CC := gcc
CFLAGS := -g -Wall -Wextra
SRCS := src/*.c
OBJS := $(SRCS:.c=.o)
OBJS =  $(SRCS:src/=obj/)
MAIN := hacky

.PHONY: depend clean

all: $(MAIN)
	@echo  hacky compiled \(\:

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o obj/$@

clean:
	$(RM) $(MAIN) obj/*.o *~

depend: $(SRCS)
	makedepend $^

# DO NOT DELETE
