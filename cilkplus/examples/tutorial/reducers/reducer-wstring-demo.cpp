/*
 * reducer-wstring-demo.cpp
 *
 * This program demonstrates using a reducer_string reducer to gather
 * a string of "wide" letters, inserting characters at the end of the
 * string. At the end of the parallel region, the string contains the
 * letters a-z is in order.
 */

#include <cilk/cilk.h>
#include <cilk/reducer_string.h>
#include <string>
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
 * locked_string_test
 *
 * Example of building a string using a mutex.  Note that:
 *  - STL strings are not thread-safe so we must use a mutex to guard
 *    access to the string.
 *  - While the mutex guarantees that the access is thread-safe, it doesn't
 *    make any guarantees about ordering, so the resulting stringt will be
 *    jumbled and diffent on every run with more than 1 worker.
 */
void locked_string_test()
{
    mutex m;
    std::wstring s;

    // Build the string
    cilk_for(int ch = L'a'; ch <= L'z'; ch++)
    {
        stall();

        m.lock();
        s += ch;
        m.unlock();
    }

    // Show the resulting string
    std::wcout << L"Locked string:  " << s << std::endl;
}

/*
 * reducer_string_test
 *
 * Example of building a string using reducer_string.  Note that:
 *  - We don't need a lock to guard the string since each strand has it's own
 *    view of the string.  The views are combined by the Cilk runtime as strands
 *    sync by calling the reduce() function of the reducer's monoid.
 *  - The string is maintained in serial order.
 *  - You can only get the value of a reducer after all parallel work has been
 *    completed.
 */
void reducer_string_test()
{
    cilk::reducer_wstring s;

    // Build the string
    cilk_for(int ch = L'a'; ch <= L'z'; ch++)
    {
        stall();
        s += ch;
    }

    // Show the resulting string
    std::wcout << L"Reducer string: " << s.get_reference() << std::endl;
}

int main(int argc, char **argv)
{
    locked_string_test();
    reducer_string_test();

    return 0;
}
