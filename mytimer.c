
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

/**
 * @brief Gets the time
 *
 * @return double Returns the time
 */
double mytimer(void)
{
    struct timespec myTime;
    clock_gettime(CLOCK_REALTIME, &myTime);
    return ((double)(myTime.tv_sec+myTime.tv_nsec/ 1000000000.0));
}

//double mytimer(void)
//{
//   struct rusage ruse;
//   getrusage(RUSAGE_SELF, &ruse);
//   return( (double)(ruse.ru_utime.tv_sec+ruse.ru_utime.tv_usec / 1000000.0) );
//}