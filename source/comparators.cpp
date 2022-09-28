#include <ctype.h>
#include <assert.h>
#include "Buffer.h"

#define UNEXPECTED_MODE INT_MAX

enum
{
    STRAIGHT_BGN,
    REVERSE_BGN,
    STRAIGHT_END,
    REVERSE_END,
    NEED_TO_CHECK_END_OF_STR,
};

int bgn_compare_main_part(const char* str1, const char* str2, short mode)
{
    while (*str1 != '\0')
    {
        if (*str2 == '\0')
            return 1;
        if (!isalpha(*str1))
        {
            str1++;
            continue;
        }
        if (!isalpha(*str2))
        {
            str2++;
            continue;
        }
        if (*str1 == *str2)
        {
            str1++;
            str2++;
            continue;
        }
        switch(mode)
        {
            case STRAIGHT_BGN:
                return (*str1 - *str2);
                break;

            case REVERSE_BGN:
                return (*str2 - *str1);
                break;

            default:
                break;
        }
    }
    return NEED_TO_CHECK_END_OF_STR;
}

int end_compare_main_part(const char* str1, const char* str2, short mode)
{
    while (*str1 != '\0')
    {
        if (*str2 == '\0')
            return 1;
        if (!isalpha(*str1))
        {
            str1--;
            continue;
        }
        if (!isalpha(*str2))
        {
            str2--;
            continue;
        }
        if (*str1 == *str2)
        {
            str1--;
            str2--;
            continue;
        }
        switch(mode)
        {
            case STRAIGHT_END:
                return (*str1 - *str2);

            case REVERSE_END:
                return (*str2 - *str1);

            default:
                break;
        }
    }
    return NEED_TO_CHECK_END_OF_STR;
}

int check_end_of_str(const char* str, short mode)
{
    if (*str =='\0')
        return 0;

    switch (mode)
    {
        case STRAIGHT_BGN:
        case REVERSE_BGN:
            while (!isalpha(*str) && (*str != '\0'))
                str++;
            break;

        case STRAIGHT_END:
        case REVERSE_END:
            while (!isalpha(*str) && (*str != '\0'))
                str--;
            break;

        default:
            return 0;
    }

    if (*str == '\0')
        return 0;

    return -1;
}

int compare(const char* str1, const char* str2, short mode)
{
    assert(str1 != nullptr);
    assert(str2 != nullptr);

    switch(mode)
    {
        case STRAIGHT_BGN:
        case REVERSE_BGN:
            return bgn_compare_main_part(str1, str2, mode);

        case STRAIGHT_END:
        case REVERSE_END:
            return end_compare_main_part(str1, str2, mode);

        default:
            return UNEXPECTED_MODE;
    }
}


int straight_cmp_from_beginning (const void* line1, const void* line2)
{
    const char* str1 = ((Line*) line1)->line_ptr;
    const char* str2 = ((Line*) line2)->line_ptr;

    int res = compare(str1, str2, STRAIGHT_BGN);
    if (res == UNEXPECTED_MODE)
    {
        printf("UNEXPECTED_COMPARATOR_MODE\n");
        return 0;
    }

    if (res != NEED_TO_CHECK_END_OF_STR)
        return res;
    return check_end_of_str(str2, STRAIGHT_BGN);
}

int reverse_cmp_from_beginning  (const void* line1, const void* line2)
{
    const char* str1 = ((Line*) line1)->line_ptr;
    const char* str2 = ((Line*) line2)->line_ptr;

    int res = compare(str1, str2, REVERSE_BGN);
    if (res == UNEXPECTED_MODE)
    {
        printf("UNEXPECTED_COMPARATOR_MODE\n");
        return 0;
    }

    if (res != NEED_TO_CHECK_END_OF_STR)
        return res;
    return check_end_of_str(str2, REVERSE_BGN);
}

int straight_cmp_from_end       (const void* line1, const void* line2)
{
    Line* line1_p = (Line*) line1;
    Line* line2_p = (Line*) line2;

    const char* str1 = line1_p->line_ptr + (line1_p->length - 1);
    const char* str2 = line2_p->line_ptr + (line2_p->length - 1);

    int res = compare(str1, str2, STRAIGHT_END);
    if (res == UNEXPECTED_MODE)
    {
        printf("UNEXPECTED_COMPARATOR_MODE\n");
        return 0;
    }

    if (res != NEED_TO_CHECK_END_OF_STR)
        return res;
    return check_end_of_str(str2, STRAIGHT_END);
}

int reverse_cmp_from_end        (const void* line1, const void* line2)
{
    Line* line1_p = (Line*) line1;
    Line* line2_p = (Line*) line2;

    const char* str1 = line1_p->line_ptr + (line1_p->length - 1);
    const char* str2 = line2_p->line_ptr + (line2_p->length - 1);

    int res = compare(str1, str2, REVERSE_END);
    if (res == UNEXPECTED_MODE)
    {
        printf("UNEXPECTED_COMPARATOR_MODE\n");
        return 0;
    }

    if (res != NEED_TO_CHECK_END_OF_STR)
        return res;
    return check_end_of_str(str2, REVERSE_END);
}
