#ifndef VEC3_H
#define VEC3_H

#include <math.h>

/** A 3D vector */
typedef struct vec3;
typedef vec3 point;

/** Create a pointer to a new vec3 */
vec3 *new_vec3(double i, double j, double k);

/** Add 2 vec3's and return a new vec3 pointer*/
vec3 *add_vec3(vec3 *a, vec3 *b);

/** Subtract 2 vec3's and return a new vec3 pointer */
vec3 *sub_vec3(vec3 *a, vec3 *b);

/** Multiply a vec3 by `b` and return a new vec3 pointer */
vec3 *mult_vec3(vec3 *a, double b);

/** Calculate the cross product of two vec3's returned as a new vec3 pointer */
vec3 *cross_vec3(vec3 *a, vec3 *b);

/** Calculate the dot product of two vec3's */
double dot_vec3(vec3 *a, vec3 *b);

/** Return the length of a vec3 */
double len_vec3(vec3 *vec);

/** Return the squared length of a vec3 */
double sqr_len_vec3(vec3 *vec);

#endif