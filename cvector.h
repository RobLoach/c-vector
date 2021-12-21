
#ifndef CVECTOR_H_
#define CVECTOR_H_

#include <assert.h> /* for assert */
#include <stdlib.h> /* for malloc/realloc/free */

/**
 * @brief cvector_vector_type - The vector type used in this library
 */
#define cvector_vector_type(type) type *

/**
 * @brief cvector_capacity - gets the current capacity of the vector
 * @param vec - the vector
 * @return the capacity as a size_t
 */
#define cvector_capacity(vec)                                                                                          \
    ((vec) == NULL ? (size_t) 0 : ((size_t *) (vec))[-1])                                                              \

/**
 * @brief cvector_size - gets the current size of the vector
 * @param vec - the vector
 * @return the size as a size_t
 */
#define cvector_size(vec)                                                                                              \
    ((vec) == NULL ? (size_t) 0 : ((size_t *) (vec))[-2])                                                              \

/**
 * @brief cvector_empty - returns non-zero if the vector is empty
 * @param vec - the vector
 * @return non-zero if empty, zero if non-empty
 */
#define cvector_empty(vec)                                                                                             \
  (cvector_size(vec) == 0)                                                                                             \

/**
 * @brief cvector_erase - removes the element at index i from the vector
 * @param vec - the vector
 * @param i - index of element to remove
 * @return void
 */
#define cvector_erase(vec, i)                                                                                          \
    do {                                                                                                               \
        if ((vec) != NULL) {                                                                                           \
            const size_t cv_sz = cvector_size(vec);                                                                    \
            if ((i) < cv_sz) {                                                                                         \
                __cvector_set_size((vec), cv_sz - 1);                                                                  \
                memmove((vec) + i, (vec) + i + 1, cv_sz - 1);                                                          \
            }                                                                                                          \
        }                                                                                                              \
    } while (0)                                                                                                        \

/**
 * @brief cvector_free - frees all memory associated with the vector
 * @param vec - the vector
 * @return void
 */
#define cvector_free(vec)                                                                                              \
    do {                                                                                                               \
        if ((vec) != NULL) {                                                                                           \
            size_t *p1 = &((size_t *) (vec))[-2];                                                                      \
            free(p1);                                                                                                  \
        }                                                                                                              \
    } while (0)                                                                                                        \

/**
 * @brief cvector_begin - returns an iterator to first element of the vector
 * @param vec - the vector
 * @return a pointer to the first element (or NULL)
 */
#define cvector_begin(vec)                                                                                             \
    (vec)                                                                                                              \

/**
 * @brief cvector_end - returns an iterator to one past the last element of the vector
 * @param vec - the vector
 * @return a pointer to one past the last element (or NULL)
 */
#define cvector_end(vec)                                                                                               \
    ((vec == NULL) ? NULL : &((vec)[cvector_size(vec)]))                                                               \

/* user request to use logarithmic growth algorithm */
#ifdef CVECTOR_LOGARITHMIC_GROWTH

/**
 * @brief cvector_push_back - adds an element to the end of the vector
 * @param vec - the vector
 * @param value - the value to add
 * @return void
 */
#define cvector_push_back(vec, value)                                                                                  \
    do {                                                                                                               \
        size_t cv_cap = cvector_capacity(vec);                                                                         \
        if (cv_cap <= cvector_size(vec)) {                                                                             \
            __cvector_grow((vec), cv_cap ? cv_cap * 2 : cv_cap + 1);                                                   \
        }                                                                                                              \
        vec[cvector_size(vec)] = (value);                                                                              \
        __cvector_set_size((vec), cvector_size(vec) + 1);                                                              \
    } while (0)                                                                                                        \

#else

/**
 * @brief cvector_push_back - adds an element to the end of the vector
 * @param vec - the vector
 * @param value - the value to add
 * @return void
 */
#define cvector_push_back(vec, value)                                                                                  \
    do {                                                                                                               \
        size_t cv_cap = cvector_capacity(vec);                                                                         \
        if (cv_cap <= cvector_size(vec)) {                                                                             \
            __cvector_grow((vec), cv_cap + 1);                                                                         \
        }                                                                                                              \
        vec[cvector_size(vec)] = (value);                                                                              \
        __cvector_set_size((vec), cvector_size(vec) + 1);                                                              \
    } while (0)                                                                                                        \

#endif /* CVECTOR_LOGARITHMIC_GROWTH */

/**
 * @brief cvector_pop_back - removes the last element from the vector
 * @param vec - the vector
 * @return void
 */
#define cvector_pop_back(vec)                                                                                          \
    do {                                                                                                               \
        __cvector_set_size((vec), cvector_size(vec) - 1);                                                              \
    } while (0)                                                                                                        \

/**
 * @brief cvector_copy - copy a vector
 * @param dest - destination to which the function copy to
 * @param src - the original vector
 * @return void
 */
#define cvector_copy(dest, src)                                                                                        \
    do {                                                                                                               \
        if (src != NULL) {                                                                                             \
            const size_t sz = cvector_size(src);                                                                       \
            __cvector_set_capacity(dest, cvector_capacity(src));                                                       \
            __cvector_set_size(dest, sz);                                                                              \
            memcpy((dest), (src), sz * sizeof(*(src)));                                                                \
        }                                                                                                              \
    } while (0)                                                                                                        \

/**
 * @brief __cvector_set_capacity - For internal use, sets the capacity variable of the vector
 * @param vec - the vector
 * @param size - the new capacity to set
 * @return void
 */
#define __cvector_set_capacity(vec, size)                                                                              \
    do {                                                                                                               \
        if ((vec) != NULL) {                                                                                           \
            ((size_t *) (vec))[-1] = (size);                                                                           \
        }                                                                                                              \
    } while (0)                                                                                                        \

/**
 * @brief __cvector_set_size - For internal use, sets the size variable of the vector
 * @param vec - the vector
 * @param size - the new capacity to set
 * @return void
 */
#define __cvector_set_size(vec, size)                                                                                  \
    do {                                                                                                               \
        if ((vec) != NULL) {                                                                                           \
            ((size_t *) (vec))[-2] = (size);                                                                           \
        }                                                                                                              \
    } while (0)                                                                                                        \

/**
 * @brief __cvector_grow - For internal use, ensures that the vector is at least <count> elements big
 * @param vec - the vector
 * @param count - the new capacity to set
 * @return void
 */
#define __cvector_grow(vec, count)                                                                                     \
    do {                                                                                                               \
        const size_t cv_sz = (count) * sizeof(*(vec)) + (sizeof(size_t) * 2);                                          \
        if (vec == NULL) {                                                                                             \
            size_t *cv_p = malloc(cv_sz);                                                                              \
            assert(cv_p);                                                                                              \
            (vec) = (void *) (&cv_p[2]);                                                                               \
            __cvector_set_capacity((vec), (count));                                                                    \
            __cvector_set_size((vec), 0);                                                                              \
        } else {                                                                                                       \
            size_t *cv_p1 = &((size_t *) (vec))[-2];                                                                   \
            size_t *cv_p2 = realloc(cv_p1, (cv_sz));                                                                   \
            assert(cv_p2);                                                                                             \
            (vec) = (void *) (&cv_p2[2]);                                                                              \
            __cvector_set_capacity((vec), (count));                                                                    \
        }                                                                                                              \
    } while (0)                                                                                                        \

#endif /* CVECTOR_H_ */
