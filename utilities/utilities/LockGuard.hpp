/**
 * @file    LockGuard.hpp
 * @author  LaverWinEmpty@google.com
 * @brief   lock guard uses typename or int as id for locking
 * @version 1.0
 * @date    2023-10-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LWE__LOCKGUARD_H__
#define LWE__LOCKGUARD_H__

#include "mutex"
#include "atomic"
#include "../../common/common/macro.hpp"

/**
 * @brief lock guard, using inner class (Mutex<id> / Spin<id>)
 *
 * @warning id: const int
 */
class LockGuard
{
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
        void Lock();
        void Unlock();
    private:
        std::mutex instance;
    };

    /**
     * @brief wrapper
     */
    class WrappedAtomic
    {
    public:
        void Lock();
        void Unlock();
    private:
        std::atomic_flag instance;
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
    template<int> struct AtomicSingleN
    {
        static WrappedAtomic wrapper;
    };

    /**
     * @brief wrapper singleton
     *
     * @tparam id
     */
    template<typename T> struct AtomicSingleT
    {
        static WrappedAtomic wrapper;
    };

public:
    /**
     * @brief object
     *
     * @tparam N object id: const int
     *
     * @warning redundant lock => runtime error
     */
    template<int N> class Mutex: public ILock<MutexSingleN<N>>
    {
    public:
        Mutex(IN bool = true);
    };

    /**
     * @brief object
     *
     * @tparam N object id: const int
     *
     * @warning redundant lock => infinite loop
     */
    template<int N> class Spin: public ILock<AtomicSingleN<N>>
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
     *
     * @warning redundant lock => runtime error
     */
    class Mutex: public LockGuard::ILock<LockGuard::MutexSingleT<T>>
    {
    public:
        Mutex(IN bool = true);
    };

    /**
     * @brief object
     *
     * @warning redundant lock => infinite loop
     */
    class Spin: public LockGuard::ILock<LockGuard::AtomicSingleT<T>>
    {
    public:
        Spin(IN bool = true);
    };
};

#include "LockGuard.ipp"
#endif