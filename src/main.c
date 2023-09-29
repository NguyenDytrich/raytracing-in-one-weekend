#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <inttypes.h>

#include "color.h"
#include "vec3.h"

// Image dimensions
int WIDTH = 256;
int HEIGHT = 256;

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

  printf("Creating %dx%d image to 'out.ppm'...\n", HEIGHT, WIDTH);
  FILE *file = fopen("out.ppm", "wb");

  // P3 header
  fprintf(file, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

  // Generate the image top to bottom, with each row generated left to right
  for (int i = 0; i < HEIGHT; i++)
  {
    for (int j = 0; j < WIDTH; j++)
    {
      color *px = new_color((double)i / (WIDTH - 1), (double)j / (HEIGHT - 1), 0);
      fprint_color(file, px);
      free(px);
      print_progress_bar((i * WIDTH) + j + 1, WIDTH * HEIGHT, 20);
    }
  }
  fclose(file);
  printf("\nDone! (%" PRIu64 "ms)\n\e[?25h", ms_time() - start);

  return 0;
}