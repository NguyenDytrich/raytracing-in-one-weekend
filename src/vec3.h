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

/** Create a new vec3 */
vec3 new_vec3(double i, double j, double k);

/** Add 2 vec3's and output to *out */
void add_vec3(vec3 a, vec3 b, vec3 *out);

/** Subtract 2 vec3's and output to *out */
void sub_vec3(vec3 a, vec3 b, vec3 *out);

/** Multiply a vec3 by `b` and output to *out */
void mult_vec3(vec3 a, double b, vec3 *out);

/** Divide a vec3 by `b` and output to *out */
void div_vec3(vec3 a, double b, vec3 *out);

/** Calculate the cross product of two vec3's and output to *out */
void cross_vec3(vec3 a, vec3 b, vec3 *out);

void unit_vec3(vec3 vec, vec3 *out);

/** Calculate the dot product of two vec3's */
double dot_vec3(vec3 a, vec3 b);

/** Return the length of a vec3 */
double len_vec3(vec3 vec);

/** Return the squared length of a vec3 */
double sqr_len_vec3(vec3 vec);

/**
 * Returns a ray on `vec` as calculated from the `origin` point using the formula
 * `P(t) = A + tB`
 * Where `A` is the ray origin, `B` is the direction (represented by a vec3) and
 * `t` is a real number
 */
void ray_at(ray r, double t, point3 *out);

/**
 * Creates a new struct of a ray with pointers to the corresponding vec3 arguments.
 */
ray new_ray(point3 *origin, vec3 *direction);

#endif