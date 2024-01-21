#ifndef CONVERTER_LAYER_H
#define CONVERTER_LAYER_H

unsigned int roundup_and_align(unsigned int val, unsigned int round_to);
void forward_converter_layer(int conv_type, int *in_int8, float *in_fp32, int *out_int, float *out_fp32);

#endif