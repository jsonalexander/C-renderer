#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

typedef struct vector
{
    double x;
    double y;
    double z;
} vector_t;

typedef struct matrix
{
    vector_t a;
    vector_t b;
    vector_t c;
} matrix_t;

#endif