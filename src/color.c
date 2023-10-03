#include "color.h"

void fprint_color(FILE *file, color pixel)
{
  fprintf(file, "%d %d %d\n", (int)(255.999 * pixel.e[0]), (int)(255.999 * pixel.e[1]), (int)(255.999 * pixel.e[2]));
}

color new_color(double r, double g, double b)
{
  return new_vec3(r, g, b);
}

color ray_color(ray r, hittable *world, int size_world)
{
  ray_t rt = {
      0,
      INFINITY};

  hit h;
  if (list_collision(world, size_world, r, rt, &h))
  {
    color c;
    add_vec3(h.normal, new_color(1, 1, 1), &c);
    mult_vec3(c, 0.5, &c);
    return c;
  };

  vec3 unit;
  unit_vec3(*(r.direction), &unit);

  // Sky color
  double a = 0.5 * (unit.e[1] + 1.0);
  color final;
  color c1 = new_color(1.0, 1.0, 1.0);
  color c2 = new_color(0.5, 0.7, 1.0);

  color c1_mult;
  mult_vec3(c1, 1.0 - a, &c1_mult);
  color c2_mult;
  mult_vec3(c2, a, &c2_mult);

  add_vec3(c1_mult, c2_mult, &final);

  return final;
}