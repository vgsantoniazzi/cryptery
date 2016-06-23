/*
 * temp_space.h
 *
 * Class to allocate temporary memory. The constructor will allocate an array
 * of "k" elements, and destructor will free the memory when it goes out of
 * scope.
 *
 * As an optimization, the object contains an array of elements that fits
 * within 4096 bytes. If the array needed is larger than 4096 bytes, the
 * memory will be allocated from the heap.
 */

template<typename T>
class temp_space
{
    static const size_t n = 4096/sizeof(T);
    T temp[n];
    T* base;
public:
    T* data() { return base; }
    T& operator[](size_t k) { return base[k]; }
    temp_space(size_t size)
    {
        base = (size <= n) ? temp : new T[size];
    }
    ~temp_space()
    {
        if (base!=temp)
            delete[] base;
    }
};
