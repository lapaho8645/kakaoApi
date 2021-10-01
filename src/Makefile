TARGET = parser.out
INC = -I../include
CFLAGS = -Wall -W $(INC)
LFLAGS = -Wall -W -ljansson

CFILES = main.c	\
		 socket.c\
		 parse.c\

OBJS = $(CFILES:.c=.o)
.c.o : $(CFILES)
	$(CC) -c $(CFLAGS) $*.c

$(TARGET) : $(OBJS) 
	$(CC) -o $(TARGET) $(OBJS) $(LFLAGS)

clean :: 
	rm -f $(OBJS) $(TARGET)
