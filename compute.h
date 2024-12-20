#ifndef __COMPUTE_H__
#define __COMPUTE_H__

#include "data_structures.h"

// vector operations

double dot(vector_t * a, vector_t * b);

vector_t cross(vector_t * a, vector_t * b);

double norm(vector_t * v);

vector_t direction(vector_t * v);

vector_t vector_transform(matrix_t * T, vector_t * v);

// vector arithmetic

vector_t vector_add(vector_t * a, vector_t * b);

vector_t vector_subtract(vector_t * a, vector_t * b);

vector_t vector_multiply(vector_t * a, vector_t * b);

vector_t vector_divide(vector_t * a, vector_t * b);

vector_t vector_scale(vector_t * v, double factor);

// matrices

matrix_t matrix_multiply(matrix_t * A, matrix_t * B);

matrix_t matrix_transpose(matrix_t * M);

matrix_t matrix_rotate(double theta_x, double theta_y, double theta_z);

// debug

void print_matrix(matrix_t * M);

void print_vector(vector_t * v);

#endif