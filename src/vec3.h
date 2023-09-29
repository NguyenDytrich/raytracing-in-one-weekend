#ifndef VEC3_H
#define VEC3_H

#include <stdlib.h>
#include <math.h>

/** A 3D vector */
typedef struct vec3
{
  double e[3];
} vec3;

typedef vec3 point3;

typedef struct ray
{
  point3 *origin;
  vec3 *direction;
} ray;

/** Create a pointer to a new vec3 */
vec3 *
new_vec3(double i, double j, double k);

/** Add 2 vec3's and return a new vec3 pointer*/
vec3 *add_vec3(vec3 *a, vec3 *b);

/** Subtract 2 vec3's and return a new vec3 pointer */
vec3 *sub_vec3(vec3 *a, vec3 *b);

/** Multiply a vec3 by `b` and return a new vec3 pointer */
vec3 *mult_vec3(vec3 *a, double b);

/** Divide a vec3 by `b` and return a new vec3 pointer */
vec3 *div_vec3(vec3 *a, double b);

/** Calculate the cross product of two vec3's returned as a new vec3 pointer */
vec3 *cross_vec3(vec3 *a, vec3 *b);

vec3 *unit_vec3(vec3 *vec);

/** Calculate the dot product of two vec3's */
double dot_vec3(vec3 *a, vec3 *b);

/** Return the length of a vec3 */
double len_vec3(vec3 *vec);

/** Return the squared length of a vec3 */
double sqr_len_vec3(vec3 *vec);

/**
 * Returns a ray on `vec` as calculated from the `origin` point using the formula
 * `P(t) = A + tB`
 * Where `A` is the ray origin, `B` is the direction (represented by a vec3) and
 * `t` is a real number
 */
point3 *ray_at(ray r, double t);

/**
 * Creates a new struct of a ray with pointers to the corresponding vec3 arguments.
 */
ray new_ray(point3 *origin, vec3 *direction);

#endif