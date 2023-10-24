/**
 * @file  type.hpp
 * @author LaverWinEmpty
 * @brief
 * @version 0.1.0
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LWE__TYPES_HPP__
#define LWE__TYPES_HPP__

#ifndef _SSIZE_T_DEFINED_
#    define _SSIZE_T_DEFINED_
#    ifdef X64
using ssize_t = int64_t;
#    else
using ssize_t = int32_t;
#    endif
#endif

/**
 * @brief address movable void* wrapper
 * @note  operator only,  address + / - value is possible
 */
class Ptr
{
    void* address;
public:
    Ptr(IN const void* param = nullptr): address(const_cast<void*>(param)) {}
    Ptr&                      operator=(IN const void* param) { return address = const_cast<void*>(param), *this; }
    Ptr&                      operator++() { return address = static_cast<int8_t*>(address) + 1, *this; }
    Ptr&                      operator--() { return address = static_cast<int8_t*>(address) - 1, *this; }
    Ptr                       operator++(OPT int) { return Ptr((operator++(), static_cast<int8_t*>(address) - 1)); }
    Ptr                       operator--(OPT int) { return Ptr((operator--(), static_cast<int8_t*>(address) + 1)); }
    template<typename T> Ptr  operator+(IN T param) const { return Ptr(reinterpret_cast<int8_t*>(address) + param); }
    template<typename T> Ptr  operator-(IN T param) const { return Ptr(reinterpret_cast<int8_t*>(address) - param); }
    template<typename T> Ptr& operator+=(IN T param) { return address = static_cast<int8_t*>(address) + param, *this; }
    template<typename T> Ptr& operator-=(IN T param) { return address = static_cast<int8_t*>(address) - param, *this; }
    template<typename T> operator T() const { return reinterpret_cast<T>(address); }
};

#endif