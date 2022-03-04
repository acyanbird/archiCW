#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

/**
 * @brief Gets the time
 * 
 * @return double Returns the time
 */
double mytimer(void)
{
   struct rusage ruse;
   getrusage(RUSAGE_SELF, &ruse);
   return( (double)(ruse.ru_utime.tv_sec+ruse.ru_utime.tv_usec / 1000000.0) );
}