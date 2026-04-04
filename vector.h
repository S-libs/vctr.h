#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    size_t capacity;
    size_t size;
} VectorHeader;

#define vec_header(v) ((VectorHeader *)(v) - 1)
#define vec_size(v) ((v) ? vec_header(v)->size : 0)
#define vec_capacity(v) ((v) ? vec_header(v)->capacity : 0)


#define vec_push(v, val) do { \
    if (!(v) || vec_size(v) == vec_capacity(v)) { \
        size_t new_cap = (v) ? vec_capacity(v) * 2 : 2; \
        void *ptr = realloc((v) ? vec_header(v) : NULL, sizeof(VectorHeader) + new_cap * sizeof(*(v))); \
        if (ptr) { \
            if (!(v)) ((VectorHeader *)ptr)->size = 0; \
            (v) = (void *)((VectorHeader *)ptr + 1); \
            vec_header(v)->capacity = new_cap; \
        } \
    } \
    (v)[vec_header(v)->size++] = (val); \
} while(0)


#define vec_remove(v, idx) do { \
    if ((v) && (idx) < vec_size(v)) { \
        memmove(&(v)[idx], &(v)[idx + 1], (vec_size(v) - (idx) - 1) * sizeof(*(v))); \
        vec_header(v)->size--; \
    } \
} while(0)


#define vec_free(v) do { \
    if (v) { free(vec_header(v)); (v) = NULL; } \
} while(0)

#endif
