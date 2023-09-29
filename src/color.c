#include "color.h"

void fprint_color(FILE *file, color *pixel)
{
  fprintf(file, "%d %d %d\n", (int)(255.999 * pixel->e[0]), (int)(255.999 * pixel->e[1]), (int)(255.999 * pixel->e[2]));
}

color *new_color(double r, double g, double b)
{
  return new_vec3(r, g, b);
}

color *ray_color(ray r)
{
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