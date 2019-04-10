#include "utils.h"

double timevalsub(const struct timeval *start, const struct timeval *end) {
  double res = 0;
  res = end->tv_sec - start->tv_sec;
  res += (end->tv_usec - start->tv_usec) * 1.0 / 1000000;
  return res;
}
