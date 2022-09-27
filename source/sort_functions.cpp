#include <assert.h>
#include "Common.h"

void my_bubble_sort(void* array, size_t number_of_elements, size_t size, int(*compare)(const void*, const void*))
{
    assert(array              != nullptr);
    assert(number_of_elements !=    0   );
    assert(size               !=    0   );

    char* array1 = (char*) array;

    for (size_t i = 0;   i < (size*number_of_elements - size);   i += size)
    {
        for (size_t j = (size*number_of_elements - size);   j > i;   j -= size)
        {
            if (compare(array1 + j - size, array1 + j) > 0)
            {
                swap (array1 + j, array1 + j - size, size);
            }
        }
    }
}

size_t partition(char* array, size_t number_of_elements, size_t size, int(*compare)(const void*, const void*), size_t pivot)
{
    assert(array != nullptr);
    assert(number_of_elements != 0);

    size_t left_hold = 0;
    size_t right_hold = number_of_elements - 1;

    while (left_hold < right_hold)
    {
        while ( (left_hold < right_hold) && (compare(array + left_hold*size, array + pivot*size) <= 0) )
        {
            left_hold++;
        }

        while ( (left_hold < right_hold) && (compare(array + right_hold*size, array + pivot*size) >= 0) )
        {
            right_hold--;
        }

        if (left_hold < right_hold)
        {
            swap(array + left_hold*size, array + right_hold*size, size);
            left_hold++;
            right_hold--;
        }
    }

    return left_hold;
}

void my_qsort(void* array, size_t number_of_elements, size_t size, int(*compare)(const void*, const void*))
{
    assert(array              != nullptr);
    assert(number_of_elements !=    0   );
    assert(size               !=    0   );

    char* array1 = (char*) array;

    if (number_of_elements <= 1)
    {
        return;
    }

    else if (number_of_elements == 2)
    {
        if (compare(array1, array1 + size) > 0)
        {
            swap(array1, array1 + size, size);
        }
        return;
    }

    size_t pivot = number_of_elements / 2;
    size_t pivot_new = partition(array1, number_of_elements, size, compare, pivot);

    my_qsort(array1, pivot_new, size, compare);
    my_qsort(array1 + (pivot_new + 1)*size, number_of_elements - pivot_new - 1, size, compare);
}
