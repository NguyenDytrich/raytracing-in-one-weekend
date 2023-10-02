#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include <math.h>

#include "vec3.h"

typedef struct hit
{
  point3 p;
  vec3 normal;
  double t;
  bool front_face;
} hit;

typedef struct hittable
{
  bool (*__collision)(void *data, ray r, double r_tmin, double r_tmax, hit *hit_out);
  void *data;
} hittable;

typedef struct sphere
{
  point3 center;
  double radius;
} sphere;

/** Check if a ray hits an object */
bool collision(hittable obj, ray r, double r_tmin, double r_tmax, hit *hit_out);
bool list_collision(hittable *objs, int size_objs, ray r, double r_tmin, double r_tmax, hit *hit_out);

bool __hit_sphere(void *_s, ray r, double ray_tmin, double ray_tmax, hit *hit_out);

hittable new_sphere(point3 center, double radius);
#endif