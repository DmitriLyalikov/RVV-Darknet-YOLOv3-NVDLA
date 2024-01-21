#include "converter.h"
#include <math.h>
#include <stdio.h>
#include "util.h"


static double int_to_fp_elmt(int in_element)
{
    // ignored post_scale and offset, because post_scale always 1 and offset always 0;
    
    // FIXME: use double just to apple-to-apple compare with AMOD; float should be fine
    // for demo which provide better perf;
    double scale = 0.34917664527893066;
    double shifter = pow(2.0, 0);

    double out_value;
    out_value = ((double)in_element) * scale/shifter;

    return out_value;
}

    double round(double x) {
    double integerPart = (double)(long long)(x);  // Extract the integer part
    double fractionalPart = x - integerPart;     // Extract the fractional part

    // If the fractional part is exactly 0.5, we need to apply "round half to even" rule
    if (fractionalPart == 0.5) {
        if ((long long)(integerPart) % 2 != 0) {
            // If the integer part is odd, round up
            integerPart += 1.0;
        }
    } else if (fractionalPart > 0.5) {
        // If the fractional part is greater than 0.5, round up
        integerPart += 1.0;
    }

    return integerPart;
}
 

/**
 * Converts from in_element double to int in specified range
 * [min_value, max_value]
 **/
static long long int fp_to_int_elmt(double in_element, long long int min_value, long long int max_value)
{
    double scale = 0.16518650949001312;
    double shifter = pow(2.0, 0);
    double post_scale = 1;
    double offset =  0;
    double post_offset = 0;
    double scaled = (in_element - offset) * scale/shifter;

    long long int out_value;
    if(isnan(in_element)) {
        out_value = min_value;
    }
    else {
        if (scaled > max_value)
            out_value = max_value;
        else if(scaled < min_value)
            out_value = min_value;
        else
            out_value = round(scaled);
    }

    out_value = out_value * ((long long int)post_scale)
                    - (long long int)post_offset;
    if (out_value > max_value)
        out_value = max_value;
    else if (out_value < min_value)
        out_value = min_value;

    return out_value;
}

// This is used in condition 1
void fp32_to_uint8(float *in, int *out, unsigned count)
{
    unsigned i;
    int min_value = 0;
    int max_value = 255;

    for (i = 0; i < count; i++) {
        long long int out_value =
            fp_to_int_elmt(in[i], min_value, max_value);
        out[i] = (int)out_value;
    }
}

// This is used in condition 2
void int8_to_fp32(int *in, float *out, unsigned int count)
{

    int8_fp_32_hwacha(count, in, out);
}