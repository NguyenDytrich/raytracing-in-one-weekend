#include <math.h>
#include "vec3.h"

vec3 *new_vec3(double i, double j, double k)
{
  struct vec3 *vec = malloc(sizeof(struct vec3));
  vec->e[0] = i;
  vec->e[1] = j;
  vec->e[2] = k;
  return vec;
}

vec3 *add_vec3(vec3 *a, vec3 *b)
{
  struct vec3 *result = new_vec3(
      a->e[0] + b->e[0],
      a->e[1] + b->e[1],
      a->e[2] + b->e[2]);
  return result;
}

vec3 *sub_vec3(vec3 *a, vec3 *b)
{
  vec3 *result = new_vec3(
      a->e[0] - b->e[0],
      a->e[1] - b->e[1],
      a->e[2] - b->e[2]);
  return result;
}

vec3 *mult_vec3(vec3 *a, double b)
{
  vec3 *result = new_vec3(
      a->e[0] * b,
      a->e[1] * b,
      a->e[2] * b);
  return result;
}

vec3 *div_vec3(vec3 *a, double b)
{
  vec3 *result = mult_vec3(a, 1 / b);
  return result;
}

vec3 *cross_vec3(vec3 *a, vec3 *b)
{
  struct vec3 *result = new_vec3(
      (a->e[1] * b->e[2]) - (a->e[2] * b->e[1]),
      (a->e[2] * b->e[0]) - (a->e[0] * b->e[2]),
      (a->e[0] * b->e[1]) - (a->e[1] * b->e[0]));
  return result;
}

vec3 *unit_vec3(vec3 *vec)
{
  return div_vec3(vec, len_vec3(vec));
}

double dot_vec3(vec3 *a, vec3 *b)
{
  return (a->e[0] * b->e[0]) + (a->e[1] * b->e[1]) + (a->e[2] * b->e[2]);
}

double sqr_len_vec3(vec3 *vec)
{
  return (vec->e[0] * vec->e[0]) + (vec->e[1] * vec->e[1]) + (vec->e[2] * vec->e[2]);
}

double len_vec3(vec3 *vec)
{
  return sqrt(sqr_len_vec3(vec));
}

ray new_ray(point3 *origin, vec3 *direction)
{
  ray r = {origin, direction};
  return r;
}

point3 *ray_at(ray r, double t)
{
  // Implements A + tB
  vec3 *tB = mult_vec3(r.direction, t);
  point3 *p = add_vec3(r.origin, tB);
  free(tB); // mult_vec3 creates a new *vec3, so free it since we don't need it anymore
  return p;
}