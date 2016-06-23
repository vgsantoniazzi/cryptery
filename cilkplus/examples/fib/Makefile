# Makefile for Unix builds

SRC := fib.cpp

all : build run

run:
	./fib.o

build : $(SRC)
	$(CXX) $(CXXFLAGS) -o fib.o $(SRC)

clean :
	rm -f fib.o
