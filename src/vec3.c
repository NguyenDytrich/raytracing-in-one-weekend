#include <math.h>
#include "vec3.h"

struct vec3 *new_vec3(double i, double j, double k)
{
  struct vec3 *vec = malloc(sizeof(struct vec3));
  vec->e[0] = i;
  vec->e[1] = j;
  vec->e[2] = k;
  return vec;
}

struct vec3 *add_vec3(vec3 *a, vec3 *b)
{
  struct vec3 *result = new_vec3(
      a->e[0] + b->e[0],
      a->e[1] + b->e[1],
      a->e[2] + b->e[2]);
  return result;
}

struct vec3 *sub_vec3(vec3 *a, vec3 *b)
{
  struct vec3 *result = new_vec3(
      a->e[0] - b->e[0],
      a->e[1] - b->e[1],
      a->e[2] - b->e[2]);
  return result;
}

struct vec3 *mult_vec3(vec3 *a, double b)
{
  struct vec3 *result = new_vec3(
      a->e[0] * b,
      a->e[1] * b,
      a->e[2] * b);
  return result;
}

struct vec3 *cross_vec3(vec3 *a, vec3 *b)
{
  struct vec3 *result = new_vec3(
      (a->e[1] * b->e[2]) - (a->e[2] * b->e[1]),
      (a->e[2] * b->e[0]) - (a->e[0] * b->e[2]),
      (a->e[0] * b->e[1]) - (a->e[1] * b->e[0]));
  return result;
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