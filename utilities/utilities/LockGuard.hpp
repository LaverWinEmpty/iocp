/**
 * @file    LockGuard.hpp
 * @author  LaverWinEmpty@google.com
 * @brief   lock guard uses typename or int as id for locking
 * @version 0.0.2
 * @date    2023-10-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LWE__LOCKGUARD_HPP__
#define LWE__LOCKGUARD_HPP__

#if _WIN32 || _WIN64
#    include "windows.h"
#else
#    include "pthread.h"
#endif
#include "../../include/include/includes.hpp"

/**
 * @brief lock guard, using inner class (Mutex<id> / Spin<id>)
 * @note  id: const int
 */
class LockGuard abstract
{
#ifdef _WINDOWS_
    using MutexType = CRITICAL_SECTION;
#else
    using MutexType = pthread_mutex_t;
#endif

#ifdef _WINDOWS_
    using SpinType = CRITICAL_SECTION;
#else
    using SpinType = pthread_spinlock_t;
#endif

public:
    /**
     * @brief INTERFACE:
     *
     * @tparam T lock object type
     */
    template<typename T> interface ILock abstract
    {
    public:
        ILock(IN bool);

    protected:
        virtual ~ILock();

    public:
        void Lock();
        void Unlock();
    };

private:
    /**
     * @brief wrapper
     */
    class WrappedMutex
    {
    public:
        WrappedMutex();
        ~WrappedMutex();
    public:
        /** @note first call unconditionally */
        void Lock();
        /** @warning called first: processing abnomally */
        void Unlock();
    private:
        MutexType instance;
        uint32_t  count;
    };

    /**
     * @brief wrapper
     */
    class WrappedSpin
    {
    public:
        WrappedSpin();
        ~WrappedSpin();
    public:
        /** @note first call unconditionally */
        void Lock();
        /** @warning called first: processing abnomally */
        void Unlock();
    private:
        SpinType instance;
        uint32_t count;
    };

public:
    /**
     * @brief wrapper singleton
     *
     * @tparam id
     */
    template<int> struct MutexSingleN
    {
        static WrappedMutex wrapper;
    };

    /**
     * @brief wrapper singleton
     *
     * @tparam id
     */
    template<typename T> struct MutexSingleT
    {
        static WrappedMutex wrapper;
    };

    /**
     * @brief wrapper singleton
     *
     * @tparam id
     */
    template<int> struct SpinSingleN
    {
        static WrappedSpin wrapper;
    };

    /**
     * @brief wrapper singleton
     *
     * @tparam id
     */
    template<typename T> struct SpinSingleT
    {
        static WrappedSpin wrapper;
    };

public:
    /**
     * @brief object
     * @warning redundant lock => runtime error
     *
     * @tparam N object id: const int
     */
    template<int N> class Mutex: public ILock<MutexSingleN<N>>
    {
    public:
        Mutex(IN bool = true);
    };

    /**
     * @brief object
     * @warning redundant lock => infinite loop
     *
     * @tparam N object id: const int
     */
    template<int N> class Spin: public ILock<SpinSingleN<N>>
    {
    public:
        Spin(IN bool = true);
    };
};

/**
 * @brief lock guard, using type name as id
 *
 * @tparam T object id: type to lock
 */
template<typename T> class TypeLock
{
public:
    /**
     * @brief object
     * @warning redundant lock => runtime error
     */
    class Mutex: public LockGuard::ILock<LockGuard::MutexSingleT<T>>
    {
    public:
        Mutex(IN bool = true);
    };

    /**
     * @brief object
     * @warning redundant lock => infinite loop
     */
    class Spin: public LockGuard::ILock<LockGuard::SpinSingleT<T>>
    {
    public:
        Spin(IN bool = true);
    };
};

#include "LockGuard.ipp"
#endif