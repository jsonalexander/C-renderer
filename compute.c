#include <stdio.h>
#include <math.h>

#include "compute.h"

double dot(vector_t * a, vector_t * b)
{
    double x = a->x * b->x;
    double y = a->y * b->y;
    double z = a->z * b->z;

    return x + y + z;
}

vector_t vector_scale(vector_t * v, double factor)
{
    double x = factor * v->x;
    double y = factor * v->y;
    double z = factor * v->z;

    return (vector_t) {x,y,z};
}

vector_t vector_subtract(vector_t * a, vector_t * b)
{
    double x = a->x - b->x;
    double y = a->y - b->y;
    double z = a->z - b->z;

    return (vector_t) {x,y,z};
}

vector_t vector_multiply(vector_t * a, vector_t * b)
{
    double x = a->x * b->x;
    double y = a->y * b->y;
    double z = a->z * b->z;

    return (vector_t) {x,y,z};
}

vector_t vector_divide(vector_t * a, vector_t * b)
{
    double x = a->x / b->x;
    double y = a->y / b->y;
    double z = a->z / b->z;

    return (vector_t) {x,y,z};
}

vector_t cross(vector_t * a, vector_t * b)
{
    double x = a->y * b->z - a->z * b->y;
    double y = -(a->x * b->z - a->z * b->x);
    double z = a->x * b->y - a->y * b->x;

    return (vector_t) {x,y,z};
}

vector_t direction(vector_t * v)
{
    double magnitude = norm(v);

    double x = v->x / magnitude;
    double y = v->y / magnitude;
    double z = v->z / magnitude;

    return (vector_t) {x,y,z};
}

double norm(vector_t * v)
{
    return sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2)); 
}

vector_t vector_transform(matrix_t * T, vector_t * v)
{
    double x = dot(&(T->a), v);
    double y = dot(&(T->b), v);;
    double z = dot(&(T->c), v);;

    return (vector_t) {x,y,z};
}

matrix_t matrix_multiply(matrix_t * A, matrix_t * B)
{
    matrix_t C = matrix_transpose(B);

    vector_t a;
    vector_t b;
    vector_t c;

    a.x = dot(&(A->a),&(C.a));
    a.y = dot(&(A->a),&(C.b));
    a.z = dot(&(A->a),&(C.c));

    b.x = dot(&(A->b),&(C.a));
    b.y = dot(&(A->b),&(C.b));
    b.z = dot(&(A->b),&(C.c));

    c.x = dot(&(A->c),&(C.a));
    c.y = dot(&(A->c),&(C.b));
    c.z = dot(&(A->c),&(C.c));

    return (matrix_t) {a,b,c};
}

matrix_t matrix_transpose(matrix_t * M)
{
    vector_t a = {M->a.x, M->b.x, M->c.x};
    vector_t b = {M->a.y, M->b.y, M->c.y};
    vector_t c = {M->a.z, M->b.z, M->c.z};

    return (matrix_t) {a,b,c};
}

matrix_t matrix_rotate(double theta_x, double theta_y, double theta_z)
{
    matrix_t R_x = {{1,0,0},{0,cos(theta_x),-sin(theta_x)},{0,sin(theta_x),cos(theta_x)}};
    matrix_t R_y = {{cos(theta_y),0,sin(theta_y)},{0,1,0},{-sin(theta_y),0,cos(theta_y)}};
    matrix_t R_z = {{cos(theta_z),-sin(theta_z),0},{sin(theta_z),cos(theta_z),0},{0,0,1}};

    matrix_t R_0 = matrix_multiply(&R_z,&R_x);
    matrix_t R = matrix_multiply(&R_0,&R_x);

    return R;
}

void print_matrix(matrix_t * M)
{
    print_vector(&M->a);
    print_vector(&M->b);
    print_vector(&M->c);
}

void print_vector(vector_t * v)
{
    printf("%.1f %.1f %.1f\n", v->x, v->y, v->z);
}