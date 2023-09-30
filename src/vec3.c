#include <math.h>
#include "vec3.h"

vec3 new_vec3(double i, double j, double k)
{
  struct vec3 vec;
  vec.e[0] = i;
  vec.e[1] = j;
  vec.e[2] = k;
  return vec;
}

void add_vec3(vec3 a, vec3 b, vec3 *out)
{
  *out = new_vec3(
      a.e[0] + b.e[0],
      a.e[1] + b.e[1],
      a.e[2] + b.e[2]);
}

void sub_vec3(vec3 a, vec3 b, vec3 *out)
{
  *out = new_vec3(
      a.e[0] - b.e[0],
      a.e[1] - b.e[1],
      a.e[2] - b.e[2]);
}

void mult_vec3(vec3 a, double b, vec3 *out)
{
  *out = new_vec3(
      a.e[0] * b,
      a.e[1] * b,
      a.e[2] * b);
}

void div_vec3(vec3 a, double b, vec3 *out)
{
  mult_vec3(a, 1 / b, out);
}

void cross_vec3(vec3 a, vec3 b, vec3 *out)
{
  *out = new_vec3(
      (a.e[1] * b.e[2]) - (a.e[2] * b.e[1]),
      (a.e[2] * b.e[0]) - (a.e[0] * b.e[2]),
      (a.e[0] * b.e[1]) - (a.e[1] * b.e[0]));
}

void unit_vec3(vec3 vec, vec3 *out)
{
  div_vec3(vec, len_vec3(vec), out);
}

double dot_vec3(vec3 a, vec3 b)
{
  return (a.e[0] * b.e[0]) + (a.e[1] * b.e[1]) + (a.e[2] * b.e[2]);
}

double sqr_len_vec3(vec3 vec)
{
  return (vec.e[0] * vec.e[0]) + (vec.e[1] * vec.e[1]) + (vec.e[2] * vec.e[2]);
}

double len_vec3(vec3 vec)
{
  return sqrt(sqr_len_vec3(vec));
}

ray new_ray(point3 *origin, vec3 *direction)
{
  ray r = {origin, direction};
  return r;
}

void ray_at(ray r, double t, point3 *out)
{
  // Implements A + tB
  mult_vec3(*(r.direction), t, out);
  add_vec3(*(r.origin), *out, out);
}