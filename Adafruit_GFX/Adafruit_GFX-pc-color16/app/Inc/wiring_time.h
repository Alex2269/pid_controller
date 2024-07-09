#ifndef _WIRING_TIME_H_
#define _WIRING_TIME_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "clock.h"

int64_t current_timestamp_ms(void);
int64_t current_timestamp_ns(void);
uint32_t GetCurrentMicro(void);

int64_t millis(void);
int64_t micros(void);
void sleep_cycle(int64_t cycle_count);
void delay(uint32_t ms);

void sleep_cycle(int64_t cycle_count);
void delay( uint32_t ms );
void delayMicroseconds(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_TIME_H_ */
