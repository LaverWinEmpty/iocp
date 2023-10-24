/**
 * @file    singleton.hpp
 * @author  LaverWinEmpty@google.com
 * @brief   singleton maker class
 * @version 0.0.1
 * @date    2023-10-24
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LWE__SINGLETON_HPP__
#define LWE__SINGLETON_HPP__

#include "../../include/include/includes.hpp"

/**
 * @brief   singleton maker (manager class)
 * @warning allow the creation of other instances
 *
 * @tparam T set singleton type
 */
template<typename T> class Singleton
{
private:
    /**
     * @brief constructor
     * @note  not working
     */
    Singleton();

    /**
     * @brief destructor
     * @note  not working
     */
    ~Singleton();

public:
    /**
     * @brief getter
     *
     * @return T* instance
     */
    static T* Instance();

public:
    /**
     * @brief call default constructor
     */
    static void Initialize();

    /**
     * @brief call copy constructor
     */
    static void Initialize(IN const T&);

    /**
     * @brief call move constructor
     */
    static void Initialize(IN const T&&);

public:
    /**
     * @brief call external initializer
     */
    static void Initialize(IN void (T::*)());

public:
    /**
     * @brief   serialization
     * @note    can call private constructor ignoring access modifier
     * @warning used for sequential data (e.g. {int, int} / forbidden: {int, pass, int})
     * @warning pointer case: pre-allocation
     *
     * @tparam Arg parameter type
     * @param size_t [in] begin pos (when use, real: current pos)
     * @param Arg    [in] parameter
     */
    template<typename Arg> static void Initialize(IN size_t offset, IN Arg arg);

    /**
     * @brief   serialization
     * @note    can call private constructor ignoring access modifier
     * @warning used for sequential data (e.g. {int, int} / forbidden: {int, pass, int})
     * @warning pointer case: pre-allocation
     *
     * @tparam Arg  parameter type
     * @tparam Args parameter pack for variadic template
     * @param size_t [in] begin pos (when use, real: current pos)
     * @param Arg    [in] parameter
     * @param Args   [in] parameter pack
     */
    template<typename Arg, typename... Args> static void Initialize(IN size_t, IN Arg, IN Args...);

private:
    /**
     * @brief object use to singleton
     * @note  eager allocation
     */
    static T* instance;
};

#include "Singleton.ipp"
#endif