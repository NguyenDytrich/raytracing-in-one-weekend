#include "mymem.h"

int _BYTES_ALLOCATED = 0;
void *my_malloc(int size)
{
  _BYTES_ALLOCATED += size;
  return malloc(size);
}

int bytes_allocated()
{
  return _BYTES_ALLOCATED;
}