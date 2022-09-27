#include <assert.h>

void swap(void* ptr1, void* ptr2, size_t size)
{
    assert(ptr1 != nullptr);
    assert(ptr2 != nullptr);
    assert(size !=    0   );

    char buf = 0;
    for (size_t i = 0; i < size; i++)
    {
        buf = *( ((char*) ptr1) + i );
        *( ((char*) ptr1) + i ) = *( ((char*) ptr2) + i );
        *( ((char*) ptr2) + i ) = buf;
    }
}
