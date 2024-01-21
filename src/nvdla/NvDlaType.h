/*
 * Copyright (c) 2017-2018, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef NVDLA_NVDLA_TYPE_C_H
#define NVDLA_NVDLA_TYPE_C_H

#include "dlaerror.h"
#include "dlatypes.h"

#include "NvDlaType.h"

#define NVDLA_DATA_FORMAT_UNKNOWN   0U
#define NVDLA_DATA_FORMAT_NCHW      1U
#define NVDLA_DATA_FORMAT_NHWC      2U
#define NVDLA_DATA_FORMAT_NCxHWx    3U

#define NVDLA_DATA_TYPE_UNKNOWN 0U
#define NVDLA_DATA_TYPE_FLOAT   1U
#define NVDLA_DATA_TYPE_HALF    2U
#define NVDLA_DATA_TYPE_INT16   3U
#define NVDLA_DATA_TYPE_INT8    4U

#define NVDLA_DATA_CATEGORY_IMAGE   0U
#define NVDLA_DATA_CATEGORY_WEIGHT  1U
#define NVDLA_DATA_CATEGORY_FEATURE 2U
#define NVDLA_DATA_CATEGORY_PLANAR  3U
#define NVDLA_DATA_CATEGORY_BIAS    4U

#define NVDLA_WEIGHT_PACKING_UNKNOWN      0U
#define NVDLA_WEIGHT_PACKING_UNCOMPRESSED 1U
#define NVDLA_WEIGHT_PACKING_COMPRESSED   2U

#define NVDLA_PIXEL_FORMAT_R8 0U
#define NVDLA_PIXEL_FORMAT_R10 1U
#define NVDLA_PIXEL_FORMAT_R12 2U
#define NVDLA_PIXEL_FORMAT_R16 3U
#define NVDLA_PIXEL_FORMAT_R16_I 4U
#define NVDLA_PIXEL_FORMAT_R16_F 5U
#define NVDLA_PIXEL_FORMAT_A16B16G16R16 6U
#define NVDLA_PIXEL_FORMAT_X16B16G16R16 7U
#define NVDLA_PIXEL_FORMAT_A16B16G16R16_F 8U
#define NVDLA_PIXEL_FORMAT_A16Y16U16V16 9U
#define NVDLA_PIXEL_FORMAT_V16U16Y16A16 10U
#define NVDLA_PIXEL_FORMAT_A16Y16U16V16_F 11U
#define NVDLA_PIXEL_FORMAT_A8B8G8R8 12U
#define NVDLA_PIXEL_FORMAT_A8R8G8B8 13U
#define NVDLA_PIXEL_FORMAT_B8G8R8A8 14U
#define NVDLA_PIXEL_FORMAT_R8G8B8A8 15U
#define NVDLA_PIXEL_FORMAT_X8B8G8R8 16U
#define NVDLA_PIXEL_FORMAT_X8R8G8B8 17U
#define NVDLA_PIXEL_FORMAT_B8G8R8X8 18U
#define NVDLA_PIXEL_FORMAT_R8G8B8X8 19U
#define NVDLA_PIXEL_FORMAT_A2B10G10R10 20U
#define NVDLA_PIXEL_FORMAT_A2R10G10B10 21U
#define NVDLA_PIXEL_FORMAT_B10G10R10A2 22U
#define NVDLA_PIXEL_FORMAT_R10G10B10A2 23U
#define NVDLA_PIXEL_FORMAT_A2Y10U10V10 24U
#define NVDLA_PIXEL_FORMAT_V10U10Y10A2 25U
#define NVDLA_PIXEL_FORMAT_A8Y8U8V8 26U
#define NVDLA_PIXEL_FORMAT_V8U8Y8A8 27U
#define NVDLA_PIXEL_FORMAT_Y8___U8V8_N444 28U
#define NVDLA_PIXEL_FORMAT_Y8___V8U8_N444 29U
#define NVDLA_PIXEL_FORMAT_Y10___U10V10_N444 30U
#define NVDLA_PIXEL_FORMAT_Y10___V10U10_N444 31U
#define NVDLA_PIXEL_FORMAT_Y12___U12V12_N444 32U
#define NVDLA_PIXEL_FORMAT_Y12___V12U12_N444 33U
#define NVDLA_PIXEL_FORMAT_Y16___U16V16_N444 34U
#define NVDLA_PIXEL_FORMAT_Y16___V16U16_N444 35U
#define NVDLA_PIXEL_FORMAT_FEATURE 36U
#define NVDLA_PIXEL_FORMAT_UNKNOWN 37U

#define NVDLA_PIXEL_MAPPING_PITCH_LINEAR 0U


typedef struct NvDlaDims3
{
    int c;
    int h;
    int w;
} NvDlaDims3;

typedef struct NvDlaDims4
{
    int n;
    int c;
    int h;
    int w;
} NvDlaDims4;

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

#endif /* NVDLA_NVDLA_TYPE_C_H */
