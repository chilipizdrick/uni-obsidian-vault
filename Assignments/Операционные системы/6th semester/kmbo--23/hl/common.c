#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include "common.h"

#ifdef DEBUG
int hl_debug = 1;
#else
int hl_debug = 0;
#endif

size_t arrsz(const char **arr) {
  size_t n = 0;
  do {
    n++;
  } while (arr[n][0] != '\0');
  return ++n;
}
