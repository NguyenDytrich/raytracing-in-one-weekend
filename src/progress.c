#include "progress.h"

uint64_t PREVIOUS_UPDATE = 0;
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
  if (PREVIOUS_UPDATE == 0 || delta_time >= TICK_RATE || status == max)
  {
    printf("\e[?25lProgress: [%s] (%d%%)\t%d/%d\r", bar, percentage, status, max);
    PREVIOUS_UPDATE = ms_time();
    if (percentage == 100)
    {
      printf("\n");
    }
  }
}