
#pragma once

#include <stdint.h>
#include <stdbool.h>

#define UNUSED(x) (void)(x)

#define STATIC_ASSERT(condition, message) _Static_assert(condition, message)

#define COUNT_OF(array)      (sizeof(array) / sizeof((array)[0]))
#define LAST_ELEMENT(array) ((array)[COUNT_OF(array) - 1])

#define OFFSET_OF(type, member) ((size_t)&(((type*)0)->member))

#define CONTAINER_OF(ptr, type, member) ((type*)((char*)(ptr) - OFFSET_OF(type, member)))

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
        for (uint32_t i = 1u; i < (count); ++i)             \
        {                                                   \
            if ((numbers)[i] < __minNumber)                 \
            {                                               \
                __minNumber = (numbers)[i];                 \
            }                                               \
        }                                                   \
        __minNumber;                                        \
    })

#define MAX(numbers, count)                                 \
    ({                                                      \
        typeof((numbers)[0]) __maxNumber = (numbers)[0];    \
        for (uint32_t i = 1u; i < (count); ++i)             \
        {                                                   \
            if ((numbers)[i] > __maxNumber)                 \
            {                                               \
                __maxNumber = (numbers)[i];                 \
            }                                               \
        }                                                   \
        __maxNumber;                                        \
    })

#define INDEX_OF_MIN(numbers, count)                        \
    ({                                                      \
        uint32_t __index = 0u;                              \
        typeof((numbers)[0]) __minNumber = (numbers)[0];    \
        for (uint32_t i = 1u; i < (count); ++i)             \
        {                                                   \
            if ((numbers)[i] < __minNumber)                 \
            {                                               \
                __index = i;                                \
                __minNumber = (numbers)[i];                 \
            }                                               \
        }                                                   \
        __index;                                            \
    })

#define INDEX_OF_MAX(numbers, count)                        \
    ({                                                      \
        uint32_t __index = 0u;                              \
        typeof((numbers)[0]) __maxNumber = (numbers)[0];    \
        for (uint32_t i = 1u; i < (count); ++i)             \
        {                                                   \
            if ((numbers)[i] > __maxNumber)                 \
            {                                               \
                __index = i;                                \
                __maxNumber = (numbers)[i];                 \
            }                                               \
        }                                                   \
        __index;                                            \
    })

#define SUM(numbers, count)                         \
    ({                                              \
        typeof((numbers)[0]) __total = 0;           \
        for (uint32_t i = 0u; i < (count); ++i)     \
        {                                           \
            __total += (numbers)[i];                \
        }                                           \
        __total;                                    \
    })

#define CONTAINS(array, count, value)               \
    ({                                              \
        int __found = 0;                            \
        for (uint32_t i = 0u; i < (count); ++i)     \
        {                                           \
            if ((array)[i] == (value))              \
            {                                       \
                __found = 1;                        \
                break;                              \
            }                                       \
        }                                           \
        __found;                                    \
    })

#define INDEX_OF(array, count, value)               \
    ({                                              \
        uint32_t __index = UINT32_MAX;              \
        for (uint32_t i = 0u; i < (count); ++i)     \
        {                                           \
            if ((array)[i] == (value))              \
            {                                       \
                __index = i;                        \
                break;                              \
            }                                       \
        }                                           \
        __index;                                    \
    })

