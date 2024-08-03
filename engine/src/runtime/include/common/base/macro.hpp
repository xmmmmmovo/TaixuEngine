#pragma once

/* If we are we on Windows, we want a single define for it.
 */
#if !defined(_WIN32) && (defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__))
    #define _WIN32
#endif /* _WIN32 */

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) || defined(__WIN64__) ||               \
        defined(WIN64) || defined(_WIN64) || defined(_MSC_VER) || defined(WINCE) ||                \
        defined(__MINGW32__) || defined(__CYWIN__)
    #define TX_WINDOWS
#endif

#if defined(__APPLE__)
    #define TX_APPLE
#endif

#if defined(__GNUC__)
    #define TX_GCC
#endif

#if defined(_MSC_VER)
    #define TX_MSVC
#endif

#if defined(_DEBUG) || defined(DEBUG) || !defined(NDEBUG)
    #define TX_DEBUG
#endif

#if defined(TX_FORCE_INLINE)
    #if _MSC_VER
        #define TX_INLINE __forceinline
        #define TX_NEVER_INLINE __declspec((noinline))
    #elif defined(__GNUC__)
        #define TX_INLINE inline __attribute__((__always_inline__))
        #define TX_NEVER_INLINE __attribute__((__noinline__))
    #elif defined(__CLANG__)
        #if __has_attribute(__always_inline__)
            #define TX_INLINE inline __attribute__((__always_inline__))
            #define TX_NEVER_INLINE __attribute__((__noinline__))
        #else
            #define TX_INLINE inline
            #define TX_NEVER_INLINE
        #endif
    #else
        #define TX_INLINE inline
        #define TX_NEVER_INLINE
    #endif
#else
    #define TX_INLINE inline
    #define TX_NEVER_INLINE
#endif

#define TX_NO_RETURN __attribute__((noreturn))
#define TX_NO_ESCAPE __attribute__((noescape))
#define TX_NO_INLINE __attribute__((noinline))

#define TX_UNUSED(x) (void) (x)

#define TX_ALIGNED(n) __attribute__((aligned(n)))

#define TX_ASSERT(x) assert((x))
#define TX_ASSERT_MSG(x, msg) assert((x) && (msg))

#define TX_STATIC_ASSERT(x) static_assert(x)
#define TX_STATIC_ASSERT_MSG(x, msg) static_assert(x, msg)

#define NOT_IMPL_ASSERT() assert(false && "Not implemented!");

#define TX_UNREACHABLE() assert(false)
#define TX_STATIC_UNREACHABLE static_assert(false)

#define TX_UNREACHABLE_MSG(msg) assert(false && (msg))
#define TX_STATIC_UNREACHABLE_MSG(msg) static_assert(false, msg)

#define TX_UNUSED_MSG(msg) (void) (msg)

#define NODISCARD [[nodiscard]]

/**
 * @brief Export macro
 */
#ifdef TX_WINDOWS
    #define TX_EXPORT __declspec(dllexport)
    #define TX_IMPORT __declspec(dllimport)
#else
    #define TX_EXPORT __attribute__((visibility("default")))
    #define TX_IMPORT __attribute__((visibility("default")))
#endif

#ifdef TX_GCC
    #define TX_LIKELY(x) __builtin_expect(!!(x), 1)
    #define TX_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
    #define TX_LIKELY(x) (!!(x))
    #define TX_UNLIKELY(x) (!!(x))
#endif

#define TX_UNREACHABLE_IF(x)                                                                       \
    if (TX_UNLIKELY(x)) { TX_UNREACHABLE(); }
#define TX_UNREACHABLE_IF_MSG(x, msg)                                                              \
    if (TX_UNLIKELY(x)) { TX_UNREACHABLE_MSG(msg); }

// NOLINTBEGIN

#define PROTOTYPE_GETTER_REF(type, name, ref)                                                      \
public:                                                                                            \
    [[nodiscard]] type ref name() { return _##name; }

#define PROTOTYPE_GETTER_VAL(type, name)                                                           \
public:                                                                                            \
    [[nodiscard]] type name() const { return _##name; }


#define PROTOTYPE_CONST_GETTER_REF(type, name, ref)                                                \
public:                                                                                            \
    [[nodiscard]] type const ref name() const { return _##name; }

#define PROTOTYPE_SETTER(type, name, ref)                                                          \
public:                                                                                            \
    void set_##name(type const ref value) { _##name = value; }

/**
 * @brief 简化const getter
 */
#define PROTOTYPE_DFT_ONLY_GETTER_CONST(access, type, name, default_val)                           \
    access:                                                                                        \
    type _##name{default_val};                                                                     \
                                                                                                   \
    PROTOTYPE_CONST_GETTER_REF(type, name, &)

/**
 * @brief 简化getter
 */
#define PROTOTYPE_DFT_ONLY_GETTER(access, type, name, default_val)                                 \
    PROTOTYPE_DFT_ONLY_GETTER_CONST(access, type, name, default_val)                               \
    PROTOTYPE_GETTER_REF(type, name, &)


/**
 * @brief 简化getter
 */
#define PROTOTYPE_ONLY_GETTER_CONST(access, type, name)                                            \
    PROTOTYPE_DFT_ONLY_GETTER_CONST(access, type, name, )

/**
 * @brief 简化getter
 */
#define PROTOTYPE_ONLY_GETTER(access, type, name) PROTOTYPE_DFT_ONLY_GETTER(access, type, name, )

/**
 * @brief 简化getter setter
 */
#define PROTOTYPE_DFT(access, type, name, default_val)                                             \
    PROTOTYPE_DFT_ONLY_GETTER(access, type, name, default_val)                                     \
    PROTOTYPE_SETTER(type, name, &)

/**
 * @brief 简化getter setter
 */
#define PROTOTYPE(access, type, name)                                                              \
    PROTOTYPE_DFT_ONLY_GETTER(access, type, name, )                                                \
    PROTOTYPE_SETTER(type, name, &)

///
/// 下面的都是pass by value的内容
///

/**
 * @brief 简化const getter
 */
#define PROTOTYPE_DFT_ONLY_GETTER_VALPASS(access, type, name, default_val)                         \
    access:                                                                                        \
    type _##name{default_val};                                                                     \
                                                                                                   \
    PROTOTYPE_GETTER_VAL(type, name)
/**
 * @brief 简化getter
 */
#define PROTOTYPE_ONLY_GETTER_VALPASS(access, type, name)                                          \
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(access, type, name, )

/**
 * @brief 简化getter setter
 */
#define PROTOTYPE_DFT_VALPASS(access, type, name, default_val)                                     \
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(access, type, name, default_val)                             \
    PROTOTYPE_SETTER(type, name, )

/**
 * @brief 简化getter setter
 */
#define PROTOTYPE_VALPASS(access, type, name)                                                      \
    PROTOTYPE_DFT_ONLY_GETTER_VALPASS(access, type, name, )                                        \
    PROTOTYPE_SETTER(type, name, )


// NOLINTEND

/**
 * @brief 使用delete copy trait
 */
#define DELETE_COPY_TRAIT(classname)                                                               \
public:                                                                                            \
    classname(const classname& other)              = delete;                                       \
    (classname)& operator=(const classname& other) = delete;

/**
 * @brief
 * @param MS 毫秒
 */
#define TX_SLEEP_FOR(MS) std::this_thread::sleep_for(std::chrono::milliseconds(MS));

/**
 * @brief
 * @param TIME duration time
 */
#define TX_SLEEP_UNTIL(TIME)                                                                       \
    std::this_thread::sleep_until(std::chrono::system_clock::now() + (TIME));

/**
 * @brief
 * @param NAME name存放的变量
 */
#define TX_THREAD_NAME(NAME)                                                                       \
    {                                                                                              \
        tx_stringstream ss;                                                                        \
        ss << (NAME);                                                                              \
        tx_string       name    = ss.str();                                                        \
        std::thread::id this_id = std::this_thread::get_id();                                      \
        pthread_setname_np(pthread_self(), name.c_str());                                          \
    }

/**
 * @brief
 *
 */
#define TX_THREAD_NAME_DEFAULT                                                                     \
    {                                                                                              \
        tx_stringstream ss;                                                                        \
        ss << "Thread " << std::this_thread::get_id();                                             \
        tx_string name = ss.str();                                                                 \
        pthread_setname_np(pthread_self(), name.c_str());                                          \
    }
