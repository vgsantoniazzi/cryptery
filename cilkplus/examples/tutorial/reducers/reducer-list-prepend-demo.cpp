/*
 * reducer-list-prepend-demo.cpp
 *
 * This program demonstrates using a reducer_list_prepend reducer to gather
 * a list of letters, inserting elements at the head of the list.  At the
 * end of the parallel region, the list of letters is in reverse (z-a) order.
 */

#include <cilk/cilk.h>
#include <cilk/reducer_list.h>
#include <list>
#include <iostream>

#ifdef _MSC_VER
#include <windows.h>

// Windows implementation of a mutex
class mutex
{
public:
    mutex()
    {
        ::InitializeCriticalSection(&m_cs);
    }

    ~mutex()
    {
        ::DeleteCriticalSection(&m_cs);
    }

    void lock()
    {
        ::EnterCriticalSection(&m_cs);
    }

    void unlock()
    {
        ::LeaveCriticalSection(&m_cs);
    }

private:
    CRITICAL_SECTION m_cs;
};

// Windows implementation of stall() will pause 1/10 of a second, which
// should be long enough for the continuation to have been stolen
void stall()
{
    Sleep(100);         // 100 milliseconds = .1 second
}
#else
#include <unistd.h>
// Linux implementation of a mutex
class mutex
{
public:
    mutex()
    {
        pthread_mutex_init(&m_mutex, NULL);
    }

    ~mutex()
    {
        pthread_mutex_destroy(&m_mutex);
    }

    void lock()
    {
        ::pthread_mutex_lock(&m_mutex);
    }

    void unlock()
    {
        ::pthread_mutex_unlock(&m_mutex);
    }

private:
    pthread_mutex_t m_mutex;
};

// Unix implementation of stall() will pause 1/10 of a second, which
// should be long enough for the continuation to have been stolen
void stall()
{
    usleep(100 * 1000); // 100 * 1000 microseconds = .1 second
}
#endif

/*
 * locked_list_test
 *
 * Example of creating an STL list using a mutex.  Note that:
 *  - STL lists are not thread-safe so we must use a mutex to guard
 *    access to the list.
 *  - While the mutex guarantees that the access is thread-safe, it doesn't
 *    make any guarantees about ordering, so the resulting list will be
 *    jumbled and diffent on every run with more than 1 worker.
 */
void locked_list_test()
{
    mutex m;
    std::list<char>letters;

    // Build the list
    cilk_for(char ch = 'a'; ch <= 'z'; ch++)
    {
        stall();

        m.lock();
        letters.push_front(ch);
        m.unlock();
    }

    // Show the resulting list
    std::cout << "Letters from locked list: ";
    for(std::list<char>::iterator i = letters.begin(); i != letters.end(); i++)
    {
        std::cout << " " << *i;
    }
    std::cout << std::endl;
}

/*
 * reducer_list_test
 *
 * Example of creating an STL list using reducer_list_append.  Note that:
 *  - We don't need a lock to guard the list since each strand has it's own
 *    view of the list.  The views are combined by the Cilk runtime as strands
 *    sync by calling the reducer() function of the reducer's monoid.
 *  - The list is maintained in serial order.
 *  - You can only get the value of a reducer after all parallel work has been
 *    completed.
 */
void reducer_list_test()
{
    cilk::reducer_list_prepend<char> letters_reducer;

    // Build the list
    cilk_for(char ch = 'a'; ch <= 'z'; ch++)
    {
        stall();
        letters_reducer.push_front(ch);
    }

    // Show the resulting list
    std::cout << "Letters from reducer_list:";
    const std::list<char> &letters = letters_reducer.get_value();
    for(std::list<char>::const_iterator i = letters.begin(); i != letters.end(); i++)
    {
        std::cout << " " << *i;
    }
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    locked_list_test();
    reducer_list_test();

    return 0;
}
