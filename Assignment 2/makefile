# Make file for twenty-six game program.

OBJS	= main.o twentySix.o
CC		= g++
CCFLAGS	= -Wall -Wextra -pedantic -std=c++17 -g
DEPS	= twentySix.h

all: main

main: $(OBJS)
	$(CC) $(CCFLAGS) -o main $(OBJS)

main.o:	main.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c main.cpp

twentySix.o: twentySix.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c twentySix.cpp

# -----
# clean by removing object files.

clean:
	rm $(OBJS)

