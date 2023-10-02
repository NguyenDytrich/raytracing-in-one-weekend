#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TICK_RATE 10 /** in ms */

/** Get the current epoch time in MS */
uint64_t ms_time();

/**
 * Print a progress bar with the percentage of status/max, with a length of
 * `length` characters. If the bar is at 100%, it will also print a '\n' character.
 * Otherwise, it will print out '\r'!
 */
void print_progress_bar(int status, int max, int length);