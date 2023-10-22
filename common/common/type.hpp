/**
 * @file  type.hpp
 * @author LaverWinEmpty
 * @brief
 * @version 1.0
 * @date 2023-10-22
 *
 * @copyright Copyright (c) 2021-2023
 *
 */

#ifndef LWE__TYPES_INL__
#define LWE__TYPES_INL__

#include "cstdint"

#ifndef _SSIZE_T_DEFINED_
#    define _SSIZE_T_DEFINED_
#    ifdef X64
using ssize_t = int64_t;
#    else
using ssize_t = int32_t;
#    endif
#endif

#ifndef interface
#    define interface struct
#endif

#ifndef _MSC_VER
#    define abstract
#endif

#endif