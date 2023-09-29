#include "color.h"

void fprint_color(FILE *file, color *pixel)
{
  fprintf(file, "%d %d %d\n", (int)(255.999 * pixel->e[0]), (int)(255.999 * pixel->e[1]), (int)(255.999 * pixel->e[2]));
}

void *new_color(double r, double g, double b)
{
  return new_vec3(r, g, b);
}