#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <errno.h>

#include "nmea_msg.h"

#define DECLARE_VECTOR(T) \
\
typedef struct vec_##T { \
    size_t size; \
    size_t cap; \
    T* data; \
} vec_##T; \
\
/* Initializes a new vector with the given capacity */ \
vec_##T* vec_##T##_init(size_t cap) { \
    vec_##T* vec = (vec_##T*)malloc(sizeof(size_t) + cap * sizeof(T)); \
    \
    if (!vec) { \
        errno = ENOMEM; \
        return NULL; \
    } \
    \
    vec->size = 0; \
    vec->cap = cap; \
    \
    return vec; \
} \
\
/* Adds a new element to the vector */ \
vec_##T* vec_##T##_push(vec_##T* vec, T value) { \
    if (vec->cap == vec->size) { \
        vec->cap *= 2; \
        vec_##T* result = (vec_##T*)realloc(vec, sizeof(size_t) + vec->cap * sizeof(T)); \
        \
        if (!vec->data) { \
            errno = ENOMEM; \
            return NULL; \
        } \
    } \
    \
    vec->data[vec->size++] = value; \
    return vec; \
} \
\
/* Returns a pointer to the last element in the vector without assigning a value*/ \
T* vec_##T##_push_empty(vec_##T* vec) { \
    if (vec->cap == vec->size) { \
        vec->cap *= 2; \
        vec_##T* result = (vec_##T*)realloc(vec, sizeof(size_t) + vec->cap * sizeof(T)); \
        \
        if (!vec->data) { \
            errno = ENOMEM; \
            return NULL; \
        } \
    } \
    \
    vec->size++; \
    return back(vec); \
} \
\
/* Removes the last element from the vector */ \
vec_##T* vec_##T##_pop(vec_##T* vec) { \
    if (vec->size == 0) { \
        return vec; \
    } \
    \
    vec->size--; \
    return vec; \
} \
\
/* Returns a pointer to the last element in the vector */ \
T* vec_##T##_back(vec_##T* vec) { \
    return vec->data + vec->size - 1; \
} \
\
/* Frees the memory allocated for the vector */ \
\
/* Returns a pointer to the element at the specified index in the vector */ \
T* vec_##T##_at(vec_##T* vec, size_t index) { \
    return vec->data + index; \
} \
\
/* Returns a pointer to the first element in the vector */ \
T* vec_##T##_front(vec_##T* vec) { \
    return vec->data; \
}\
void vec_##T##_free(vec_##T* vec) { \
    free(vec->data); \
    free(vec); \
} \

#endif // VECTOR_H