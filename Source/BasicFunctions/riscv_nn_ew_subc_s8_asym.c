/******************************************************************************
 * Copyright (C) 2010-2025 Arm Limited or its affiliates. All rights reserved.*
 * Copyright (C) 2018-2025 Andes Technology Corporation. All rights reserved. *
 *                                                                            *
 * SPDX-License-Identifier: Apache-2.0                                        *
 *                                                                            *
 * Licensed under the Apache License, Version 2.0 (the License); you may      *
 * not use this file except in compliance with the License.                   *
 * You may obtain a copy of the License at                                    *
 *                                                                            *
 * www.apache.org/licenses/LICENSE-2.0                                        *
 *                                                                            *
 * Unless required by applicable law or agreed to in writing, software        *
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT    *
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.           *
 * See the License for the specific language governing permissions and        *
 * limitations under the License.                                             *
 ******************************************************************************/

/** @file*/

#include "internal_nn_math.h"

//// Basic Operation Functions

int32_t riscv_nn_ew_subc_s8_asym(const int8_t * in_vec,
                                 const int32_t in_const,
                                 const int32_t in_offset,//range:[-128, 127]
                                 const int32_t in_scale,
                                 const int32_t in_rshift,
                                 const int32_t lshift,  // 23
                                 int8_t * out_vec,
                                 const int32_t out_offset,//range:[-128, 127]
                                 const int32_t out_scale,
                                 const int32_t out_rshift,
                                 const int32_t act_min,
                                 const int32_t act_max,
                                 const uint32_t size)
{
    int32_t in, out;
    uint32_t loop = size;

    while (loop > 0)
    {
        in = (*in_vec++ + in_offset) << lshift;
        in = riscv_nn_requantize_ns(in, in_scale, -in_rshift);

        out = in - in_const;
        out = riscv_nn_requantize_ns(out, out_scale, -out_rshift);
        out += out_offset;
        out = MAX(out, act_min);
        out = MIN(out, act_max);

        *out_vec++ = out;
        loop--;
    }
    return 0;
}
