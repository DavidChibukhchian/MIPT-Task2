#ifndef TASK2_SORT_FUNCTIONS_H
#define TASK2_SORT_FUNCTIONS_H

void swap(void* ptr1, void* ptr2, size_t size);

void my_bubble_sort(void* array, size_t number_of_elements, size_t size, int(*compare)(const void*, const void*));

void my_qsort(void* array, size_t number_of_elements, size_t size, int(*compare)(const void*, const void*));

#endif //TASK2_SORT_FUNCTIONS_H
