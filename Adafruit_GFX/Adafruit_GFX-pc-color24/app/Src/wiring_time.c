#ifdef __cplusplus
extern "C" {
#endif

#include "wiring_time.h"

#include <time.h>
#include <sys/time.h>

/**
*
* ┌───────────────────┬───────────────┬─────────┐
* │ Interface         │ Attribute     │  Value  │
* ├───────────────────┼───────────────┼─────────┤
* │ usleep()          │ Thread safety │ MT-Safe │
* └───────────────────┴───────────────┴─────────┘
*
**/

int64_t current_timestamp_ms(void)
{
  struct timeval te;
  gettimeofday(&te, NULL); // get current time
  int64_t milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
  // printf("milliseconds: %lld\n", milliseconds);
  return milliseconds;
}

int64_t current_timestamp_ns(void)
{
  struct timeval te;
  gettimeofday(&te, NULL); // get current time
  int64_t nanoseconds = (int64_t)(te.tv_sec) * (int64_t)1000000000 + (int64_t)(te.tv_usec);
  // printf("nanoseconds: %lld\n", nanoseconds);
  return nanoseconds;
}

int64_t millis(void)
{
  struct timeval te;
  gettimeofday(&te, NULL); // get current time
  int64_t milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
  // printf("milliseconds: %lld\n", milliseconds);
  return milliseconds;
}

int64_t micros(void)
{
  struct timeval te;
  gettimeofday(&te, NULL); // get current time
  int64_t nanoseconds = (int64_t)(te.tv_sec) * (int64_t)1000000000 + (int64_t)(te.tv_usec);
  // printf("nanoseconds: %lld\n", nanoseconds);
  return nanoseconds;
}

void sleep_cycle(int64_t cycle_count)
{
  int64_t count=0;
  for(count=0;count<cycle_count;count++)
  {
    __asm volatile ("nop");
  }
}

void delay(uint32_t ms)
{
  usleep(ms);
}

void delayMicroseconds(uint32_t ms)
{
  usleep(ms);
}

#ifdef __cplusplus
}
#endif
