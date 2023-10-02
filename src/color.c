#include "color.h"

void fprint_color(FILE *file, color pixel)
{
  fprintf(file, "%d %d %d\n", (int)(255.999 * pixel.e[0]), (int)(255.999 * pixel.e[1]), (int)(255.999 * pixel.e[2]));
}

color new_color(double r, double g, double b)
{
  return new_vec3(r, g, b);
}

double hit_sphere(point3 center, double radius, ray r)
{
  vec3 oc;
  sub_vec3(*(r.origin), center, &oc);
  double a = sqr_len_vec3(*(r.direction));       // V * V == len(V)**2!
  double hb = dot_vec3(oc, *(r.direction));      // 2h
  double c = sqr_len_vec3(oc) - radius * radius; // V * V == len(V)**2!
  double discriminant = hb * hb - a * c;
  if (discriminant < 0)
  {
    return -1.0;
  }
  else
  {
    return (-hb - sqrt(discriminant) / a);
  };
}

color ray_color(ray r)
{
  vec3 sphere_center = new_vec3(0, 0, -1);
  double t = hit_sphere(sphere_center, 0.5, r);

  vec3 unit;
  unit_vec3(*(r.direction), &unit);

  // If sphere is hit
  if (t > 0.0)
  {
    vec3 n;
    point3 point;

    ray_at(r, t, &point);
    sub_vec3(point, sphere_center, &n);

    vec3 n_unit;
    unit_vec3(n, &n_unit);

    color ray_color;
    mult_vec3(new_color(n_unit.e[0] + 1, n_unit.e[1] + 1, n_unit.e[2] + 1), 0.5, &ray_color);
    return ray_color;
  }

  double a = 0.5 * (unit.e[1] + 1.0);
  color c1 = new_color(1.0, 1.0, 1.0);
  color c2 = new_color(0.5, 0.7, 1.0);

  color final;

  color c1_mult;
  mult_vec3(c1, 1.0 - a, &c1_mult);
  color c2_mult;
  mult_vec3(c2, a, &c2_mult);

  add_vec3(c1_mult, c2_mult, &final);

  return final;
}