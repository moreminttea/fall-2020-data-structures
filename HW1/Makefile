# Makefile ECS36C Program 1
#

CC = g++ -std=c++17
CFLAGS = -g -Wall -Werror

# CFLAGS = -O3

#CORE_INCS =	Book.h
CORE_OBJS =	Book.o

# rules.
all: SearchNewBooks

#
#
Book.o:			Book.cpp Book.h
	$(CC) -c $(CFLAGS) Book.cpp

SearchNewBooks.o:	SearchNewBooks.cpp $(CORE_INCS)
	$(CC) -c $(CFLAGS) SearchNewBooks.cpp

SearchNewBooks:		$(CORE_OBJS) SearchNewBooks.o
	$(CC) -o SearchNewBooks $(CORE_OBJS) SearchNewBooks.o   

clean:
	rm -f *.o *~ core SearchNewBooks
