#ifndef FastPID_H
#define FastPID_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <sys/param.h> // MIN MAX

#define INTEG_MAX    (INT32_MAX)
#define INTEG_MIN    (INT32_MIN)
#define DERIV_MAX    (INT16_MAX)
#define DERIV_MIN    (INT16_MIN)

#define PARAM_SHIFT  8
#define PARAM_BITS   16
#define PARAM_MAX    (((0x1ULL << PARAM_BITS)-1) >> PARAM_SHIFT) 
#define PARAM_MULT   (((0x1ULL << PARAM_BITS)) >> (PARAM_BITS - PARAM_SHIFT)) 

void FastPID_clear(void);
bool FastPID_setCoefficients(float kp, float ki, float kd, float hz);
bool FastPID_setOutputConfig(int bits, bool sign);
bool FastPID_setOutputRange(int16_t min, int16_t max);
bool FastPID_configure(float kp, float ki, float kd, float hz, int bits, bool sign);
uint32_t FastPID_floatToParam(float in);
int16_t FastPID_step(int16_t sp, int16_t fb);
void FastPID_setCfgErr(void);

#ifdef __cplusplus
}
#endif

#endif

