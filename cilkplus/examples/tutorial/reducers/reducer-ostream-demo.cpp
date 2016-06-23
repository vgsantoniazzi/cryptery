/*
 * reducer-ostream-demo.cpp
 *
 * This program demonstrates using a reducer_ostream reducer to write
 * from parallel strands.  The reducer guarantees that the data is
 * written in the same order as if the program were run serially.
 */

#include <cilk/cilk.h>
#include <cilk/reducer_ostream.h>
#include <iostream>

#ifdef _MSC_VER
#include <windows.h>

// Windows implementation of stall() will pause 1/10 of a second, which
// should be long enough for the continuation to have been stolen
void stall()
{
    Sleep(100);         // 100 milliseconds = .1 second
}
#else
#include <unistd.h>
// Unix implementation of stall() will pause 1/10 of a second, which
// should be long enough for the continuation to have been stolen
void stall()
{
    usleep(100 * 1000); // 100 * 1000 microseconds = .1 second
}
#endif

int main(int argc, char **argv)
{
    std::cout << "Standard cout: ";
    cilk_for(int ch = 'a'; ch <= 'z'; ch++)
    {
	char buf[4] = {'\0', '\0'};

	stall();
	buf[0] = ch;
	std::cout << buf;
    }
    std::cout << std::endl;

    cilk::reducer_ostream hyper_cout(std::cout);
    hyper_cout << "Reducer cout:  ";
    cilk_for(int ch = 'a'; ch <= 'z'; ch++)
    {
	char buf[4] = {'\0', '\0'};
	stall();
	buf[0] = ch;
	hyper_cout << buf;
    }
    hyper_cout << std::endl;

    return 0;
}
