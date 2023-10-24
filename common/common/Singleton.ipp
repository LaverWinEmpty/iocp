template<typename T> Singleton<T>::Singleton() {}

template<typename T> Singleton<T>::~Singleton() {}

template<typename T> T* Singleton<T>::Instance()
{
    return instance;
}

template<typename T> void Singleton<T>::Initialize()
{
    *instance = T();
}

template<typename T> void Singleton<T>::Initialize(const T& ref)
{
    *instance = ref;
}

template<typename T> void Singleton<T>::Initialize(const T&& ref)
{
    *instance = ref;
}

template<typename T> void Singleton<T>::Initialize(void (T::*method)())
{
    (instance->*method)();
}

template<typename T>
T* Singleton<T>::instance = []() {
    T*   ptr = static_cast<T*>(malloc(sizeof(T)));
    auto fn  = []() {
        if(instance) std::free(instance);
    };
    std::atexit(fn);
    std::at_quick_exit(fn);
    return ptr;
}();

template<typename T> template<typename Arg> void Singleton<T>::Initialize(size_t offset, Arg arg)
{
    uint8_t* ptr                 = reinterpret_cast<uint8_t*>(instance) + offset;
    *reinterpret_cast<Arg*>(ptr) = arg;
}

template<typename T>
template<typename Arg, typename... Args>
void Singleton<T>::Initialize(size_t offset, Arg arg, Args... args)
{
    uint8_t* ptr                 = reinterpret_cast<uint8_t*>(instance) + offset;
    *reinterpret_cast<Arg*>(ptr) = arg;
    Initialize(offset + sizeof(Arg), args...);
}