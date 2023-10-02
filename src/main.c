#include <stdlib.h>
#include <stdio.h>

#include "color.h"
#include "vec3.h"
#include "progress.h"
#include "collision.h"

// Image dimensions
double ASPECT_RATIO = 16.0 / 9.0;
int WIDTH = 400;
double VIEWPORT_HEIGHT = 2.0;

int image_height()
{
  int height = WIDTH / ASPECT_RATIO;
  return height < 1 ? 1 : height;
}
double viewport_width()
{
  return VIEWPORT_HEIGHT * ((double)WIDTH / image_height());
}

/** Calculate a viewport upper left returning a pointer to a new vec3*/
vec3 calc_vp_upper_left(vec3 camera_center, double focal_len, vec3 viewport_u, vec3 viewport_v)
{
  vec3 du_div2;
  vec3 dv_div2;
  div_vec3(viewport_u, 2, &du_div2);
  div_vec3(viewport_v, 2, &dv_div2);

  vec3 vec_focal_len = new_vec3(0, 0, focal_len);

  vec3 diff;
  sub_vec3(camera_center, vec_focal_len, &diff);
  sub_vec3(diff, du_div2, &diff);
  sub_vec3(diff, dv_div2, &diff);

  return diff;
}

/** Calculate the pixel at (0,0) returning a pointer to a new vec3 */
vec3 calc_pixel_00_loc(vec3 vp_upper_left, vec3 px_du, vec3 px_dv)
{
  vec3 result;

  add_vec3(px_du, px_dv, &result);
  mult_vec3(result, 0.5, &result);
  add_vec3(vp_upper_left, result, &result);

  return result;
}

int main()
{
  uint64_t start = ms_time();
  int HEIGHT = image_height();

  // Camera
  double focal_len = 1.0;
  point3 camera_center = new_vec3(0, 0, 0);

  double VEIWPORT_WIDTH = viewport_width();
  // Viewport
  // Vectors represent the dimensions of the viewport, `viewport_u` is horizontal
  // and `viewport_v` is vertical
  vec3 viewport_u = new_vec3(VEIWPORT_WIDTH, 0, 0);
  vec3 viewport_v = new_vec3(0, -VIEWPORT_HEIGHT, 0);

  // Calculate delta values for pixel spacing
  vec3 pixel_du, pixel_dv;
  div_vec3(viewport_u, WIDTH, &pixel_du);
  div_vec3(viewport_v, HEIGHT, &pixel_dv);

  // Calculate position of upper left pixel
  vec3 viewport_Q = calc_vp_upper_left(camera_center, focal_len, viewport_u, viewport_v);
  vec3 pixel00_loc = calc_pixel_00_loc(viewport_Q, pixel_du, pixel_dv);

  // TODO: move this into a utility
  hittable *world = (hittable *)malloc(sizeof(hittable) * 2);
  world[0] = new_sphere(new_vec3(0, 0, -1), 0.5);
  world[1] = new_sphere(new_vec3(0, -100.5, -1), 100.0);

  printf("Creating %dx%d image to 'out.ppm'...\n", image_height(), WIDTH);
  FILE *file = fopen("out.ppm", "wb");

  // P3 header
  fprintf(file, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

  // Generate the image top to bottom, with each row generated left to right
  for (int j = 0; j < HEIGHT; j++)
  {
    for (int i = 0; i < WIDTH; i++)
    {
      // Calculate pixel center
      vec3 px_center;
      vec3 i_du, j_dv;
      mult_vec3(pixel_du, (double)i, &i_du);
      mult_vec3(pixel_dv, (double)j, &j_dv);
      add_vec3(i_du, j_dv, &px_center);
      add_vec3(pixel00_loc, px_center, &px_center);

      vec3 ray_direction;
      sub_vec3(px_center, camera_center, &ray_direction);
      ray r = new_ray(&camera_center, &ray_direction);
      color px = ray_color(r, world, sizeof(hittable) * 2);
      fprint_color(file, px);

      print_progress_bar((j * WIDTH) + i + 1, WIDTH * HEIGHT, 20);
    }
  }
  fclose(file);
  printf("Done! (%.2fs)\n\e[?25h", (double)(ms_time() - start) / 1000);

  return 0;
}