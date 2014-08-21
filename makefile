CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

OBJS = main.o

heap : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o heap

main.o : main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *.o heap




