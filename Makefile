CC = c++
CFLAGS = -std=c++20 -Wall

all: lab2

lab2: test.o
	$(CC) $(CFLAGS) -o lab2 test.o

test.o: test.cpp DynamicArray.h LinkedList.h ArraySequence.h ListSequence.h AdaptiveSequence.h Sequence.h SegmentedList.h Container.h
	$(CC) $(CFLAGS) -c test.cpp

clean:
	rm -f test.o lab2