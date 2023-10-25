template<int N> LockGuard::WrappedMutex      LockGuard::MutexSingleN<N>::wrapper;
template<typename T> LockGuard::WrappedMutex LockGuard::MutexSingleT<T>::wrapper;
template<int N> LockGuard::WrappedSpin       LockGuard::SpinSingleN<N>::wrapper;
template<typename T> LockGuard::WrappedSpin  LockGuard::SpinSingleT<T>::wrapper;

LockGuard::WrappedMutex::WrappedMutex()
{
#ifdef _WINDOWS_
    InitializeCriticalSection(&instance);
#else
    pthread_mutex_init(&instance, NULL);
#endif
}

LockGuard::WrappedMutex::~WrappedMutex()
{
#ifdef _WINDOWS_
    DeleteCriticalSection(&instance);
#else
    pthread_mutex_destroy(&instance);
#endif
}

void LockGuard::WrappedMutex::Lock()
{
#ifdef _WINDOWS_
    EnterCriticalSection(&instance);
#else
    pthread_mutex_lock(instance)
#endif
}

void LockGuard::WrappedMutex::Unlock()
{
#ifdef _WINDOWS_
    LeaveCriticalSection(&instance);
#else
    pthread_mutex_unlock(&instance);
#endif
}

LockGuard::WrappedSpin::WrappedSpin()
{
#ifdef _WINDOWS_
    InitializeCriticalSectionAndSpinCount(&instance, 4000);
#else
    pthread_spin_init(&instance, PTHREAD_PROCESS_SHARED);
#endif
}

LockGuard::WrappedSpin::~WrappedSpin()
{
#ifdef _WINDOWS_
    DeleteCriticalSection(&instance);
#else
    pthread_spin_destroy(&instance);
#endif
}

void LockGuard::WrappedSpin::Lock()
{
#ifdef _WINDOWS_
    EnterCriticalSection(&instance);
#else
    pthread_spin_lock(&instance);
#endif
    ++count;
}

void LockGuard::WrappedSpin::Unlock()
{
    if(count && --count) return;
#ifdef _WINDOWS_
    LeaveCriticalSection(&instance);
#else
    pthread_spin_unlock(&instance);
#endif
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

template<int N> LockGuard::Spin<N>::Spin(bool isLock): LockGuard::ILock<LockGuard::SpinSingleN<N>>(isLock) {}

template<typename T> TypeLock<T>::Mutex::Mutex(bool isLock): LockGuard::ILock<LockGuard::MutexSingleT<T>>(isLock) {}

template<typename T> TypeLock<T>::Spin::Spin(bool isLock): LockGuard::ILock<LockGuard::SpinSingleT<T>>(isLock) {}