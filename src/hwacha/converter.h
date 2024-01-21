#ifndef CONVERTERS_H
#define CONVERTERS_H

#include <stdint.h>

void fp32_to_uint8(float *in, int *out, unsigned count);
void int8_to_fp32(int *in, float *out, unsigned count);
#endif