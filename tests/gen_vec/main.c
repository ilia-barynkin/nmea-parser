#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

#include "../../src/nmea_msg.h"

typedef struct vec_gga_msg
{
    size_t size;
    size_t cap;
    gga_msg *data;
} vec_gga_msg;
vec_gga_msg *vec_gga_msg_init(size_t cap)
{
    vec_gga_msg *vec = (vec_gga_msg *)malloc(sizeof(size_t) + cap * sizeof(gga_msg));
    if (!vec)
    {
        (*__errno_location()) = 12;
        return (vec_gga_msg*)(NULL);
    }
    vec->size = 0;
    vec->cap = cap;
    return vec;
}
vec_gga_msg *vec_gga_msg_push(vec_gga_msg *vec, gga_msg value)
{
    if (vec->cap == vec->size)
    {
        vec->cap *= 2;
        vec_gga_msg *result = (vec_gga_msg *)realloc(vec, sizeof(size_t) + vec->cap * sizeof(gga_msg));
        if (!vec->data)
        {
            (*__errno_location()) = 12;
            return (vec_gga_msg*)(NULL);
        }
    }
    vec->data[vec->size++] = value;
    return vec;
}
gga_msg *vec_gga_msg_back(vec_gga_msg *vec) { return vec->data + vec->size - 1; }
gga_msg *vec_gga_msg_at(vec_gga_msg *vec, size_t index) { return vec->data + index; }
gga_msg *vec_gga_msg_front(vec_gga_msg *vec) { return vec->data; }
gga_msg *vec_gga_msg_push_empty(vec_gga_msg *vec)
{
    if (vec->cap == vec->size)
    {
        vec->cap *= 2;
        vec_gga_msg *result = (vec_gga_msg *)realloc(vec, sizeof(size_t) + vec->cap * sizeof(gga_msg));
        if (!vec->data)
        {
            (*__errno_location()) = 12;
            return (gga_msg*)(NULL);
        }
    }
    vec->size++;
    return vec_gga_msg_back(vec);
}
vec_gga_msg *vec_gga_msg_pop(vec_gga_msg *vec)
{
    if (vec->size == 0)
    {
        return vec;
    }
    vec->size--;
    return vec;
}
void vec_gga_msg_free(vec_gga_msg *vec)
{
    free(vec->data);
    free(vec);
}

int main(int argc, char* argv[]) {
    return 0;
}