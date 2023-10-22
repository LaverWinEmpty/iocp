/**
 * @file    LockGuard.ipp
 * @author  LaverWinEmpty@google.com
 * @brief   lockguard definition
 * @version 1.0
 * @date    2023-10-22
 *
 * @copyright Copyright (c) 2023
 */

#ifndef LWE__LOCKGUARD_IPP__
#define LWE__LOCKGUARD_IPP__

template<int N> LockGuard::WrappedMutex       LockGuard::MutexSingleN<N>::wrapper;
template<typename T> LockGuard::WrappedMutex  LockGuard::MutexSingleT<T>::wrapper;
template<int N> LockGuard::WrappedAtomic      LockGuard::AtomicSingleN<N>::wrapper;
template<typename T> LockGuard::WrappedAtomic LockGuard::AtomicSingleT<T>::wrapper;

void LockGuard::WrappedMutex::Lock()
{
    instance.lock();
}

void LockGuard::WrappedMutex::Unlock()
{
    instance.unlock();
}

void LockGuard::WrappedAtomic::Lock()
{
    while(instance.test_and_set(std::memory_order_acquire)) continue;
}

void LockGuard::WrappedAtomic::Unlock()
{
    instance.clear(std::memory_order_release);
}

template<typename T> LockGuard::ILock<T>::ILock(bool isLock)
{
    if(isLock) {
        Lock();
    }
}

template<typename T> LockGuard::ILock<T>::~ILock()
{
    Unlock();
}

template<typename T> void LockGuard::ILock<T>::Lock()
{
    T::wrapper.Lock();
}

template<typename T> void LockGuard::ILock<T>::Unlock()
{
    T::wrapper.Unlock();
}

template<int N> LockGuard::Mutex<N>::Mutex(bool isLock): LockGuard::ILock<LockGuard::MutexSingleN<N>>(isLock) {}

template<int N> LockGuard::Spin<N>::Spin(bool isLock): LockGuard::ILock<LockGuard::AtomicSingleN<N>>(isLock) {}

template<typename T> TypeLock<T>::Mutex::Mutex(bool isLock): LockGuard::ILock<LockGuard::MutexSingleT<T>>(isLock) {}

template<typename T> TypeLock<T>::Spin::Spin(bool isLock): LockGuard::ILock<LockGuard::AtomicSingleT<T>>(isLock) {}

#endif