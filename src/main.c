#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <inttypes.h>

#include "color.h"
#include "vec3.h"

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
vec3 *calc_vp_upper_left(vec3 *camera_center, double focal_len, vec3 *viewport_u, vec3 *viewport_v)
{
  vec3 *du_div_2 = div_vec3(viewport_u, 2);
  vec3 *dv_div_2 = div_vec3(viewport_v, 2);
  vec3 *vec_focal_len = new_vec3(0, 0, focal_len);

  vec3 *diff = sub_vec3(camera_center, vec_focal_len);
  vec3 *diff2 = sub_vec3(diff, du_div_2);
  vec3 *diff3 = sub_vec3(diff2, dv_div_2);

  free(vec_focal_len);
  free(du_div_2);
  free(dv_div_2);
  free(diff);
  free(diff2);

  return diff3;
}

/** Calculate the pixel at (0,0) returning a pointer to a new vec3 */
vec3 *calc_pixel_00_loc(vec3 *vp_upper_left, vec3 *px_du, vec3 *px_dv)
{
  vec3 *sum_px_delta = add_vec3(px_du, px_dv);
  vec3 *mult_result = mult_vec3(sum_px_delta, 0.5);
  vec3 *result = add_vec3(vp_upper_left, mult_result);
  free(sum_px_delta);
  free(mult_result);
  return result;
}

// Progress bar
uint64_t PREVIOUS_UPDATE = 0;
int PROGRESS_TICK_RATE = 10; /** in ms */

uint64_t ms_time()
{
  struct timespec time;
  clock_gettime(CLOCK_REALTIME, &time);
  long seconds = time.tv_sec;
  long nanoseconds = time.tv_nsec;
  return (seconds * 1000) + (nanoseconds / 1e6);
}

void print_progress_bar(int status, int max, int length)
{
  double ratio = (double)status / (double)max;
  int char_threshold = ratio * length;
  char *bar = malloc(sizeof(char) * length);

  for (int i = 0; i < sizeof(char) * length; i++)
  {
    if (i < char_threshold)
    {
      bar[i] = '#';
    }
    else
    {
      bar[i] = ' ';
    }
  }
  int percentage = status == max ? 100 : ratio * 100;
  uint64_t delta_time = (ms_time() - PREVIOUS_UPDATE);
  bar[(sizeof(char) * length) - 1] = status == max ? '#' : ' ';
  if (PREVIOUS_UPDATE == 0 || delta_time >= PROGRESS_TICK_RATE || status == max)
  {
    printf("\e[?25lProgress: [%s] (%d%%)\t%d/%d\r", bar, percentage, status, max);
    PREVIOUS_UPDATE = ms_time();
  }
}

int main()
{
  uint64_t start = ms_time();
  int HEIGHT = image_height();

  // Camera
  double focal_len = 1.0;
  point3 *camera_center = new_vec3(0, 0, 0);

  double VEIWPORT_WIDTH = viewport_width();
  // Viewport
  // Vectors represent the dimensions of the viewport, `viewport_u` is horizontal
  // and `viewport_v` is vertical
  vec3 *viewport_u = new_vec3(VEIWPORT_WIDTH, 0, 0);
  vec3 *viewport_v = new_vec3(0, -VIEWPORT_HEIGHT, 0);

  // Calculate delta values for pixel spacing
  vec3 *pixel_du = div_vec3(viewport_u, WIDTH);
  vec3 *pixel_dv = div_vec3(viewport_v, HEIGHT);

  // Calculate position of upper left pixel
  vec3 *viewport_Q = calc_vp_upper_left(camera_center, focal_len, viewport_u, viewport_v);
  vec3 *pixel00_loc = calc_pixel_00_loc(viewport_Q, pixel_du, pixel_dv);

  printf("Creating %dx%d image to 'out.ppm'...\n", image_height(), WIDTH);
  FILE *file = fopen("out.ppm", "wb");

  // P3 header
  fprintf(file, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

  // Generate the image top to bottom, with each row generated left to right
  for (int j = 0; j < HEIGHT; j++)
  {
    for (int i = 0; i < WIDTH; i++)
    {
      // color *px = new_color((double)i / (WIDTH - 1), (double)j / (HEIGHT - 1), i + j);
      // Calculate pixel center
      vec3 *i_du = mult_vec3(pixel_du, (double)i);
      vec3 *j_dv = mult_vec3(pixel_dv, (double)j);
      vec3 *sum_px_d = add_vec3(i_du, j_dv);
      vec3 *px_center = add_vec3(pixel00_loc, sum_px_d);

      vec3 *ray_direction = sub_vec3(px_center, camera_center);
      ray r = new_ray(camera_center, ray_direction);
      color *px = ray_color(r);

      fprint_color(file, px);
      free(px);
      free(i_du);
      free(j_dv);
      free(sum_px_d);
      free(px_center);
      free(ray_direction);

      print_progress_bar((i * WIDTH) + j + 1, WIDTH * HEIGHT, 20);
    }
  }
  fclose(file);
  printf("\nDone! (%" PRIu64 "ms)\n\e[?25h", ms_time() - start);

  return 0;
}