#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include <math.h>

#include "vec3.h"

/** Min an max values for ray `t` values */
typedef struct interval
{
  double min;
  double max;
} interval;

typedef interval ray_t;

typedef struct hit
{
  point3 p;
  vec3 normal;
  double t;
  bool front_face;
} hit;

typedef struct hittable
{
  bool (*__collision)(void *data, ray r, ray_t rt, hit *hit_out);
  void *data;
} hittable;

typedef struct sphere
{
  point3 center;
  double radius;
} sphere;

/** Check if a ray hits an object */
bool collision(hittable obj, ray r, ray_t rt, hit *hit_out);
bool list_collision(hittable *objs, int size_objs, ray r, ray_t rt, hit *hit_out);

hittable new_sphere(point3 center, double radius);
#endif