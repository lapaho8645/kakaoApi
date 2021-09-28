INC = -I../include
CFLAGS = -w $(INC)
LFLAGS = -w -ljansson

CFILES = main.c	\
		 socket.c\

OBJS = $(CFILES:.c=.o)
.c.o : $(CFILES)
	$(CC) -c $(CFLAGS) $*.c

parser.out: $(OBJS) 
	$(CC) -o parser.out $(OBJS) $(LFLAGS)

clean :: 
	rm -f $(OBJS)
