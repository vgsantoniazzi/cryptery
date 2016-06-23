# Makefile for Unix builds

SRC := driver.cpp karatsuba.cpp

all : build run

run :
	./karatsuba.o

build : $(SRC)
	$(CXX) $(CXXFLAGS) -o karatsuba.o $(SRC)

driver.cpp : cilk_ticks.h karatsuba.h

karatsuba.cpp : karatsuba.h temp_space.h

clean :
	rm -f karatsuba.o
	