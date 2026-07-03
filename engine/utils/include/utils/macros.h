
#pragma once

#include <stdint.h>
#include <stdbool.h>

#define UNUSED(x) ((void)(x))

#define STATIC_ASSERT(condition, message) _Static_assert(condition, message)

#define COUNT_OF(array)      (sizeof(array) / sizeof((array)[0]))
#define LAST_ELEMENT(array) ((array)[COUNT_OF(array) - 1])

#define OFFSET_OF(type, member) ((size_t)&(((type*)0)->member))

#define CONTAINER_OF(ptr, type, member) ((type*)((uint8_t*)(ptr) - OFFSET_OF(type, member)))

#define ABS(x)  (((x) > (typeof(x))0) ? (x) : -(x))

#define SMALLER(x, y)   (((x) < (y)) ? (x) : (y))
#define GREATER(x, y)   (((x) > (y)) ? (x) : (y))

#define WRAP(x, max)    (((x) % (max) + (max)) % (max))

#define CLAMP(x, min, max)  (((x) < (min)) ? (min) : ((x) > (max)) ? (max) : (x))

#define LERP(a, b, t)   ((a) + (typeof(a))(t) * ((b) - (a)))

#define SWAP(a, b)              \
    do {                        \
        typeof(a) __tmp = (a);  \
        (a) = (b);              \
        (b) = __tmp;            \
    } while (0)

#define MIN(numbers, count)                                 \
    ({                                                      \
        typeof((numbers)[0]) __minNumber = (numbers)[0];    \
        for (size_t __i = 1; __i < (count); ++__i)          \
        {                                                   \
            if ((numbers)[__i] < __minNumber)               \
            {                                               \
                __minNumber = (numbers)[__i];               \
            }                                               \
        }                                                   \
        __minNumber;                                        \
    })

#define MAX(numbers, count)                                 \
    ({                                                      \
        typeof((numbers)[0]) __maxNumber = (numbers)[0];    \
        for (size_t __i = 1; __i < (count); ++__i)          \
        {                                                   \
            if ((numbers)[__i] > __maxNumber)               \
            {                                               \
                __maxNumber = (numbers)[__i];               \
            }                                               \
        }                                                   \
        __maxNumber;                                        \
    })

#define INDEX_OF_MIN(numbers, count)                        \
    ({                                                      \
        size_t __index = 0;                                 \
        typeof((numbers)[0]) __minNumber = (numbers)[0];    \
        for (size_t __i = 1; __i < (count); ++__i)          \
        {                                                   \
            if ((numbers)[__i] < __minNumber)               \
            {                                               \
                __index = __i;                              \
                __minNumber = (numbers)[__i];               \
            }                                               \
        }                                                   \
        __index;                                            \
    })

#define INDEX_OF_MAX(numbers, count)                        \
    ({                                                      \
        size_t __index = 0;                                 \
        typeof((numbers)[0]) __maxNumber = (numbers)[0];    \
        for (size_t __i = 1; __i < (count); ++__i)          \
        {                                                   \
            if ((numbers)[__i] > __maxNumber)               \
            {                                               \
                __index = __i;                              \
                __maxNumber = (numbers)[__i];               \
            }                                               \
        }                                                   \
        __index;                                            \
    })

#define SUM(numbers, count)                         \
    ({                                              \
        typeof((numbers)[0]) __total = 0;           \
        for (size_t __i = 0; __i < (count); ++__i)  \
        {                                           \
            __total += (numbers)[__i];              \
        }                                           \
        __total;                                    \
    })

#define CONTAINS(array, count, value)               \
    ({                                              \
        bool __found = false;                       \
        for (size_t __i = 0; __i < (count); ++__i)  \
        {                                           \
            if ((array)[__i] == (value))            \
            {                                       \
                __found = true;                     \
                break;                              \
            }                                       \
        }                                           \
        __found;                                    \
    })

#define INDEX_OF(array, count, value)               \
    ({                                              \
        size_t __index = SIZE_MAX;                  \
        for (size_t __i = 0; __i < (count); ++__i)  \
        {                                           \
            if ((array)[__i] == (value))            \
            {                                       \
                __index = __i;                      \
                break;                              \
            }                                       \
        }                                           \
        __index;                                    \
    })

