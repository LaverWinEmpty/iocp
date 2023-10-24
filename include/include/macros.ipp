

#ifndef LWE__MACRO_HPP__
#define LWE__MACRO_HPP__

#if _WIN32 || _WIN64
#    if _WIN64
#        define X64
#    else
#        define X86
#    endif
#elif __GNUC__
#    if __x86_64__ || __ppc64__
#        define X64
#    else
#        define X86
#    endif
#else
#    error Unknown OS
#endif

#if defined(__BYTE_ORDER__)
#    if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#        define BIG_ENDIAN
#    elif __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#        define LITTLE_ENDIAN
#    else
#        error Unknown Endian
#    endif
#endif

#ifndef prop
/**
 * @brief property
 *
 * @param __VA_ARGS__ [in] get = getter, put = setter
 */
#    define prop(...) __declspec(property(__VA_ARGS__))
#endif

// clang-format off
#ifndef pass
/**
 * @brief do nothing
 */
#    define pass do {} while(false)
#endif
// clang-format on

#ifndef interface
#    define interface struct
#endif

#ifndef _MSC_VER
#    define abstract
#endif

#ifndef IN
#    define IN
#endif

#ifndef OUT
#    define OUT
#endif

#ifndef OPT
#    define OPT
#endif

#ifndef NULL
#    define NULL 0
#endif

#ifndef EXCEPT
#    define EXCEPT -1
#endif

#ifndef BYTE_BIT
#    define BYTE_BIT 8
#endif

#ifndef DEF_BUF_SIZE
/**
 * @brief 4kb
 */
#    define DEF_BUF_SIZE 4096
#endif

#ifndef EPSILON
/**
 * @brief float
 */
#    define EPSILON 1.192092896e-07f
#endif

#ifndef PI
/**
 * @brief double
 */
#    define PI 3.14159265358979
#endif

/**
 * @brief to string
 *
 * @param x [in]
 */
#define TO_STRING(x) #x

/**
 * @brief macro value to string
 *
 * @param x [in]
 */
#define STR_MACRO(x) TO_STRING(x)

/**
 * @brief simple concatenate
 *
 * @param x [in]
 * @param y [in]
 */
#define STR_CONCAT(x, y) TO_STRING(x)##y

/**
 * @brief
 */
#define EXPORT extern "C" __declspec(dllexport)

/**
 * @brief check big endian system
 *
 * @ return true / false
 */
#define CHECK_BIG_ENDIAN() (static_cast<bool>(*("\0\1")))

/**
 * @brief check little endian system
 *
 * @return true / false
 */
#define CHECK_LITTLE_ENDIAN() (static_cast<bool>(*("\1\0")))

/**
 * @brief const to normal
 *
 * @param from [in] type name
 * @param to [in] type name
 * @param data [in] source
 */
#define RAW_CAST(from, to, data) (reinterpret_cast<to>(const_cast<from>((data))))

/**
 * @brief cating for enum
 */
#define TO_INT(x) (static_cast<int>(x))

/**
 * @brief for WORD_PTR
 */
#define PTR_TO_WORD(x) (reinterpret_cast<size_t>((x)))

/**
 * @brief get absolute value
 *
 * @param x [in]
 */
#define ABS(x) ((x) < 0 ? -(x) : (x))

/**
 * @brief compare float / double
 *
 * @param a [in]
 * @param b [in]
 */
#define FLOAT_EQUAL(a, b) (ABS((a) - (b)) <= EPSILON)

/**
 * @brief bool to string ascii
 *
 * @param x [in]
 */
#define BOOL_ASTR(x) ((x) ? "TRUE" : "FALSE")

/**
 * @brief bool to string unicode
 *
 * @param x [in]
 */
#define BOOL_WSTR(x) ((x) ? L"TRUE" : L"FALSE")

/**
 * @brief get max
 *
 * @param a [in]
 * @param b [in]
 */
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/**
 * @brief get min
 *
 * @param a [in]
 * @param b [in]
 */
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/**
 * @brief radian to degree
 */
#define RADIAN_TO_DEGREE(radian) (radian * (180 / PI))

/**
 * @brief degree to radian
 */
#define DEGREE_TO_RADIAN(degree) (degree * (PI / 180))

/**
 * @brief lower to upper
 *
 * @param ch [in]
 */
#define TO_UPPER(ch) ((ch)-32)

/**
 * @brief upper to lower
 *
 * @param ch [in]
 */
#define TO_LOWER(ch) ((ch) | 0x20)

/**
 * @brief bit to byte
 *
 * @param x [in]
 */
#define TO_BYTE(x) (x >> 3)

/**
 * @brief byte to bit
 *
 * @param x [in]
 */
#define TO_BIT(x) (x << 3)

/**
 * @brief type size to bit
 */
#define SIZE_BIT(type) (sizeof(type) << 3)

/**
 * @brief get array data amount
 *
 * @warning don't use pointer variable
 */
#define ARRAY_ELEMENTS_COUNT(arr) (sizeof((arr)) / sizeof(*(arr)))

/**
 * @brief removes expanded filled 1-bit for safe shift
 */
#define TO_INT64(x)                                                                                                    \
    (static_cast<unsigned __int64>(x) << ((sizeof(__int64) - sizeof((x))) << 3) >>                                     \
     ((sizeof(unsigned __int64) - sizeof((x))) << 3))

/**
 * @brief shift rotate left
 */
#define SHIFT_ROT_L(x, move) (((TO_INT64(x)) << (move)) | ((TO_INT64(x)) >> (SIZE_BIT((x)) - (move))))

/**
 * @brief shift rotate right
 */
#define SHIFT_ROT_R(x, move) (((TO_INT64(x)) >> (move)) | ((TO_INT64(x)) << (SIZE_BIT((x)) - (move))))

/**
 * @brief shift rotate left
 * @warning unsigned only
 */
#define SHIFT_ROT_L_UNSIGNED(x, move) (((x) << (move)) | ((x) >> (SIZE_BIT((x)) - (move))))

/**
 * @brief shift rotate right
 *
 * @warning unsigned only
 */
#define SHIFT_ROT_R_UNSIGNED(x, move) (((x) >> (move)) | ((x) << (SIZE_BIT((x)) - (move))))

/**
 * @brief ex: 0x0011 => 0x1100
 */
#define REVERSE_ENDIAN_16(x) (((x) << 8) | (((x) & 0xFF00) >> 8))

/**
 * @brief ex: 0x00112233 => 0x33221100
 */
#define REVERSE_ENDIAN_32(x)                                                                                           \
    (((x) << 24) | (((x) & 0xFF00) << 8) | (((x) & 0xFF0000) >> 8) | (((x) & 0xFF000000) >> 24))

/**
 * @brief ex: 0x0011223344556677 => 0x7766554433221100
 */
#define REVERSE_ENDIAN_64(x)                                                                                           \
    (((x) << 56) | (((x) & 0xFF00) << 40) | (((x) & 0xFF0000) << 24) | (((x) & 0xFF000000) << 8) |                     \
     (((x) & 0xFF00000000) >> 8) | (((x) & 0xFF0000000000) >> 24) | (((x) & 0xFF000000000000) >> 40) |                 \
     (((x) & 0xFF00000000000000) >> 56))

#define DISABLE_WARNING_PUSH __pragma(warning(push)) __pragma(warning(disable : 26819))
#define DISABLE_WARNING_POP  __pragma(warning(pop))

// clang-format off
/**
 * @brief duff's device
 * @note use e.g. FAST_LOOP(100, int i = 0; int j = 1, ++i; ++j);
 * 
 * @param count     [in] loop count
 * @param init      [in] initialize
 * @param procedure [in] procedure
 */
#pragma warning(push)
#pragma warning(disable:26819)
#define FAST_LOOP(count, init, procedure)                                                                              \
    do {                                                                                                               \
        init;                                                                                                          \
        __int64 loop_count_in_fast_loop_macro = (static_cast<__int64>(count) + 7) >> 3;                                \
        if(count > 0) switch(count & 0b111) {                                                                          \
                case 0: do {                                                                                           \
                        procedure;                                                                                     \
                case 7: procedure;                                                                                     \
                case 6: procedure;                                                                                     \
                case 5: procedure;                                                                                     \
                case 4: procedure;                                                                                     \
                case 3: procedure;                                                                                     \
                case 2: procedure;                                                                                     \
                case 1: procedure;                                                                                     \
                } while(--loop_count_in_fast_loop_macro > 0);                                                          \
            }                                                                                                          \
    } while(false)                                                                                                    
#pragma warning(pop)
// clang-format on

/**
 * @brief swap macro
 */
#define SWAP(a, b)                                                                                                     \
    do {                                                                                                               \
        decltype(a) temp_in_swap_macro = (a);                                                                          \
        (a)                            = (b);                                                                          \
        (b)                            = temp_in_swap_macro;                                                           \
    } while(false)

/**
 * @brief bit on/off
 *
 * @param var   [out] variable
 * @param value [in] bit flag
 * @param isSet [in] ture: var bit on / false: var bit off
 */
#define SET_BIT_FLAG(var, value, isSet)                                                                                \
    do {                                                                                                               \
        if(isSet) {                                                                                                    \
            var |= value;                                                                                              \
        }                                                                                                              \
        else {                                                                                                         \
            var &= ~value;                                                                                             \
        }                                                                                                              \
    } while(false)

/**
 * @brief safe delete
 *
 * @param [out] ptr set nullptr
 */
#define SAFE_DELETE(ptr)                                                                                               \
    do {                                                                                                               \
        if(ptr != NULL) delete ptr;                                                                                    \
        ptr = nullptr;                                                                                                 \
    } while(false)

/**
 * @brief safe delete array
 *
 * @param [out] ptr set nullptr
 */
#define SAFE_DELETES(ptr)                                                                                              \
    do {                                                                                                               \
        if(ptr != NULL) delete[] ptr;                                                                                  \
        ptr = nullptr;                                                                                                 \
    } while(false)

/**
 * @brief safe delete
 *
 * @param [out] ptr is delete
 *
 * @warning ptr has garbage value
 */
#define SAFE_DESTRUCT(ptr)                                                                                             \
    do {                                                                                                               \
        if(ptr != NULL) delete ptr;                                                                                    \
    } while(false)

/**
 * @brief safe delete array
 *
 * @param [out] ptr is delete
 *
 * @warning ptr has garbage value
 */
#define SAFE_DESTRUCTS(ptr)                                                                                            \
    do {                                                                                                               \
        if(ptr != NULL) delete[] ptr;                                                                                  \
    } while(false)

/**
 * @brief   set singlton
 * @note    unconditionally create only a single instance
 * @warning non thread safe
 *
 * @param [in] type
 *
 * @warning use in class
 */
#define DECLARE_SINGLETON(type)                                                                                        \
    static void CreateInstance()                                                                                       \
    {                                                                                                                  \
        if(instance == nullptr) {                                                                                      \
            instance = new type();                                                                                     \
        }                                                                                                              \
    }                                                                                                                  \
    static void DestroyInstance()                                                                                      \
    {                                                                                                                  \
        if(instance != nullptr) {                                                                                      \
            delete instance;                                                                                           \
        }                                                                                                              \
    }                                                                                                                  \
    static type* GetInstance()                                                                                         \
    {                                                                                                                  \
        return instance;                                                                                               \
    }

/**
 * @brief declare instance
 *
 * @warning use in class
 */
#define DECLARE_SINGLETON_INSTANCE(type) static type* instance

/**
 * @brief definition instance
 */
#define DEFINE_SINGLETON_INSTANCE(Type) Type* Type::instance = nullptr

/**
 * @brief get singleton instance
 */
#define INSTANCE(Type) Type::GetInstance()

/**
 * @brief set static class
 */
#define DECLARE_LIMIT_LIFECYCLE(Type)                                                                                  \
    Type()  = delete;                                                                                                  \
    ~Type() = delete

/**
 * @brief set no copy
 */
#define DECLARE_NO_COPY(Type)                                                                                          \
    Type(const Type&)            = delete;                                                                             \
    Type& operator=(const Type&) = delete

/**
 * @brief enum to bit flag
 *
 * @param e [in] enum type name use as bit flag
 */
#define DEFINE_ENUM_TO_FLAG(e)                                                                                         \
    e operator|(IN e a, IN e b)                                                                                        \
    {                                                                                                                  \
        return static_cast<e>(static_cast<int>(a) | static_cast<int>(b));                                              \
    }                                                                                                                  \
    e operator&(IN e a, IN e b)                                                                                        \
    {                                                                                                                  \
        return static_cast<e>(static_cast<int>(a) & static_cast<int>(b));                                              \
    }                                                                                                                  \
    e operator^(IN e a, IN e b)                                                                                        \
    {                                                                                                                  \
        return static_cast<e>(static_cast<int>(a) ^ static_cast<int>(b));                                              \
    }                                                                                                                  \
    e& operator|=(IN OUT e& a, IN e b)                                                                                 \
    {                                                                                                                  \
        return a = a | b, a;                                                                                           \
    }                                                                                                                  \
    e& operator&=(IN OUT e& a, IN e b)                                                                                 \
    {                                                                                                                  \
        return a = a & b, a;                                                                                           \
    }                                                                                                                  \
    e& operator^=(IN OUT e& a, IN e b)                                                                                 \
    {                                                                                                                  \
        return a = a ^ b, a;                                                                                           \
    }                                                                                                                  \
    e operator~(IN e a)                                                                                                \
    {                                                                                                                  \
        return static_cast<e>(~static_cast<int>(a));                                                                   \
    }

#define DECLARE_BLOCK(bit)                                                                                             \
    struct Block##bit                                                                                                  \
    {                                                                                                                  \
        uint8_t& operator[](IN ssize_t index)                                                                          \
        {                                                                                                              \
            return data[index];                                                                                        \
        }                                                                                                              \
        Block##bit(const int8_t* str): data{ 0 }                                                                       \
        {                                                                                                              \
            int loop = TO_BYTE(bit);                                                                                   \
            FAST_LOOP(loop, int i = 0, data[i] = str[i]; ++i);                                                         \
        }                                                                                                              \
        template<typename... Args> Block##bit(Args... args): data{ 0 }                                                 \
        {                                                                                                              \
            Ctor(0, args...);                                                                                          \
        }                                                                                                              \
        template<typename T> operator T()                                                                              \
        {                                                                                                              \
            return reinterpret_cast<T>(data);                                                                          \
        }                                                                                                              \
    private:                                                                                                           \
        template<typename T, typename... Args> void Ctor(ssize_t index, T arg, Args... args)                           \
        {                                                                                                              \
            data[index] = static_cast<T>(arg);                                                                         \
            if(index >= TO_BYTE(bit)) {                                                                                \
                throw std::out_of_range(EErrMsg::OUT_OF_RANGE);                                                        \
            }                                                                                                          \
            Ctor(index + 1, args...);                                                                                  \
        }                                                                                                              \
        void Ctor(ssize_t index)                                                                                       \
        {                                                                                                              \
            return;                                                                                                    \
        }                                                                                                              \
        uint8_t data[TO_BYTE(bit)];                                                                                    \
    }

#endif