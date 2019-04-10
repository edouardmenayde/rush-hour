#ifndef RUSH_HOUR_UTILS_H
#define RUSH_HOUR_UTILS_H

#include <sys/time.h>

/**
 * Compute time it takes
 * @param start
 * @param end
 * @return {end - start}
 */
double timevalsub(const struct timeval *start, const struct timeval *end);

#endif //RUSH_HOUR_UTILS_H
