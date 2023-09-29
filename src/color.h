#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

#include "vec3.h"

typedef vec3 color;

/** Writes a pixel to a .ppm file */
void fprint_color(FILE *file, color *pixel);

/** Create a new RGB color */
void *new_color(double r, double g, double b);

#endif