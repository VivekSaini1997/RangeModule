CXX = g++
CXXFLAGS = -std=gnu++17 -g -Wall -Wextra -Wpedantic
DEPS = Range.h Tests.h

%.o : %.c $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

all: Range.o main.o Tests.o
	$(CXX) $(CXXFLAGS) *.o -o range

clean:
	rm -f *.o

full:
	make clean; make