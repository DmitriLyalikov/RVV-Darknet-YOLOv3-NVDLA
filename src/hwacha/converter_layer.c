#include "converter_layer.h"
#include "converter.h"
#include <stdlib.h>
#include <stdio.h>
#include <riscv-pk/encoding.h>
#include "util.h"
// These functions will be mapped to Hwacha 
//extern void fp32_to_uint8(float *in, int *out, unsigned count);
//extern void int8_to_fp32(int *in, float *out, unsigned count);

/**
 * Convert a 3D array with the NCHW (number of samples, channels, height, width)
 * data layout to (samples, height, width, channels)
 * 
 * 
*/
/* 
void convert_nchw_to_nhwc(int *in, int w, int h, int c, int *out)
{
    // over each channel (0 - (c-1))
    for (int i = 0; i < c; i++) {
        // over the height (0 - (h-1))
        for (int j = 0; j < h; j++) {
            // over the width (0 - (w-1))
            for (int k = 0; k < w; k++) {
                // calculate index for both the NCHW and NHWC arrays
                out[j*w*c + c*k + i] = in[w*h*i + w*j + k];
            }
        }
    }
} */
/*
*  Convert feature depth layout to NCHW (samples, channels, height, width)
*  FD layout organizes data witha depth of 32 channels per element while the NCHW layout arranges
*  data by samples
*/
/* 
void convert_fd_to_nchw(float *in, int w, int h, int c, float *out)
{   
    // number of elements in a single row
    unsigned int line_stride = w * 32; 
    // number of elements in a single surface (32 channels) of the FD input 
    unsigned int surface_stride = line_stride * h;
    // over each channel (0 - c1)
    for (int i = 0; i < c; i++) {
        // over the height (0 - (h-1))
        for (int j = 0; j < h; j++) {
            // over the width (0 - (w-1))
            for (int k = 0; k < w; k++) {
                // calculate the surface index with integer division by 32 to identify surface
                int surface_index = i/32;
                // calculate proper index
                out[w*h*i + w*j + k] = in[surface_stride*surface_index + line_stride*j + 32*k + i%32];
            }
        }
    }
}
*/

void forward_converter_layer(int conv_type, int *in_int8, float *in_fp32, int *out_int, float *out_fp32)
{
    /* Make a call to precision converter */
    // l.outputs * l.batch
    unsigned count = 5 * 5 * 3;
    // l.out_w * l.out_h * roundup_and_align(l.out_c, 32);
    unsigned int bufsize = 5 * 5 * 32;
    printf("Allocated inside of conversion layer\n");
    // CASE 1: Convert from FP32 to UINT8
    if (conv_type == 1) {
        int *temp = calloc(bufsize, sizeof(int));
        fp32_to_uint8(in_fp32, temp, count);
        convert_nchw_to_nhwc(temp, 4, 4, 32, (int*)out_int);
        free(temp);
    } else
    // CASE 2: Convert from INT8 to FP32
    {
        float *temp = calloc(bufsize, sizeof(float));
        unsigned long start_conv, end_conv, end_nchw;
        start_conv = rdcycle();
	//printf("starting int8_fp_32 func\n");
        int8_to_fp32(in_int8, temp, count);
	// printf("exit itofp32 func\n");
        end_conv = rdcycle();
	    printf("Conversion Function cyles: %lu\n", end_conv - start_conv);

        // Convert from feature depth layout to NCHW
        convert_fd_to_nchw(temp, 5, 5, 3, out_fp32);
        end_nchw = rdcycle();
        printf("Conversion Function cyles: %lu\n", end_conv - start_conv);
        printf("Feature depth to NCHW cyles: %lu\n", end_nchw - end_conv);
        free(temp);
    }
}