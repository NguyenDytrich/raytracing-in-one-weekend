#include <stdbool.h>

#include "color.h"

void fprint_color(FILE *file, color *pixel)
{
  fprintf(file, "%d %d %d\n", (int)(255.999 * pixel->e[0]), (int)(255.999 * pixel->e[1]), (int)(255.999 * pixel->e[2]));
}

color *new_color(double r, double g, double b)
{
  return new_vec3(r, g, b);
}

bool hit_sphere(point3 *center, double radius, ray r)
{
  vec3 *oc = sub_vec3(r.origin, center);
  double a = dot_vec3(r.direction, r.direction);
  double b = 2.0 * dot_vec3(oc, r.direction);
  double c = dot_vec3(oc, oc) - radius * radius;
  double discriminant = b * b - 4 * a * c;
  free(oc);
  return (discriminant >= 0);
}

color *ray_color(ray r)
{
  vec3 *sphere_center = new_vec3(0, 0, -1);
  if (hit_sphere(sphere_center, 0.5, r))
  {
    return new_color(1, 0, 0);
  }
  free(sphere_center);

  vec3 *unit = unit_vec3(r.direction);
  double a = 0.5 * (unit->e[1] + 1.0);
  color *c1 = new_color(1.0, 1.0, 1.0);
  color *c2 = new_color(0.5, 0.7, 1.0);

  color *c1_mult = mult_vec3(c1, 1.0 - a);
  color *c2_mult = mult_vec3(c2, a);
  color *sum = add_vec3(c1_mult, c2_mult);

  free(unit);
  free(c1);
  free(c1_mult);
  free(c2);
  free(c2_mult);

  return sum;
}