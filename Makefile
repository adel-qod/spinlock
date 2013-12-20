CC = g++
CFLAGS = -pedantic -W -Wall -std=c++11 -O3
OBJS = Spinlock.o test_suit.o
LFLAGS = -lpthread

Spinlock: $(OBJS)
	$(CC) $(CFLAGS) -o spinlock_test_suit $(OBJS) $(LFLAGS)

test_suit.o: test_suit.cc
	$(CC) $(CFLAGS) -c test_suit.cc

Spinlock.o: Spinlock.cc
	$(CC) $(CFLAGS) -c Spinlock.cc

clean:
	rm spinlock_test_suit *.o
