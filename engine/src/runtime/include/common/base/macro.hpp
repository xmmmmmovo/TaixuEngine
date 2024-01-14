#ifndef ENGINE_RUNTIME_CORE_BASE_MACRO
#define ENGINE_RUNTIME_CORE_BASE_MACRO

/* If we are we on Windows, we want a single define for it.
 */
#if !defined(_WIN32) &&                                                        \
        (defined(__WIN32__) || defined(WIN32) || defined(__MINGW32__))
    #define _WIN32
#endif /* _WIN32 */

#if defined(__WIN32__) || defined(WIN32) || defined(_WIN32) ||                 \
        defined(__WIN64__) || defined(WIN64) || defined(_WIN64) ||             \
        defined(_MSC_VER)
    #define TX_WINDOWS
#endif

#if !defined(_DEBUG) && defined(DEBUG)
    #define _DEBUG
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
#define TX_ASSERT_MSG(x, msg) assert((x) && msg)

#define TX_UNREACHABLE() assert(false)

// NOLINTBEGIN

#define PROTOTYPE_GETTER(type, name)                                           \
public:                                                                        \
    [[nodiscard]] inline type& name() { return _##name; }

#define PROTOTYPE_CONST_GETTER(type, name)                                     \
public:                                                                        \
    [[nodiscard]] inline type const& name() const { return _##name; }

#define PROTOTYPE_SETTER(type, name)                                           \
public:                                                                        \
    inline void set_##name(type const& value) { _##name = value; }

/**
 * @brief 简化const getter
 */
#define PROTOTYPE_DFT_ONLY_GETTER_CONST(access, type, name, default_val)       \
access:                                                                        \
    type _##name{default_val};                                                 \
                                                                               \
    PROTOTYPE_CONST_GETTER(type, name)

/**
 * @brief 简化getter
 */
#define PROTOTYPE_DFT_ONLY_GETTER(access, type, name, default_val)             \
    PROTOTYPE_DFT_ONLY_GETTER_CONST(access, type, name, default_val)           \
    PROTOTYPE_GETTER(type, name)


/**
 * @brief 简化getter
 */
#define PROTOTYPE_ONLY_GETTER_CONST(access, type, name)                        \
    PROTOTYPE_DFT_ONLY_GETTER_CONST(access, type, name, )

/**
 * @brief 简化getter
 */
#define PROTOTYPE_ONLY_GETTER(access, type, name)                              \
    PROTOTYPE_DFT_ONLY_GETTER(access, type, name, )

/**
 * @brief 简化getter setter
 */
#define PROTOTYPE_DFT(access, type, name, default_val)                         \
    PROTOTYPE_DFT_ONLY_GETTER(access, type, name, default_val)                 \
    PROTOTYPE_SETTER(type, name)

/**
 * @brief 简化getter setter
 */
#define PROTOTYPE(access, type, name)                                          \
    PROTOTYPE_DFT_ONLY_GETTER(access, type, name, )                            \
    PROTOTYPE_SETTER(type, name)

// NOLINTEND

/**
 * @brief 使用delete copy trait
 */
#define DELETE_COPY_TRAIT(classname)                                           \
public:                                                                        \
    classname(const classname& other)              = delete;                   \
    (classname)& operator=(const classname& other) = delete;

/**
 * @brief
 * @param MS 毫秒
 */
#define TX_SLEEP_FOR(MS)                                                       \
    std::this_thread::sleep_for(std::chrono::milliseconds(MS));

/**
 * @brief
 * @param TIME duration time
 */
#define TX_SLEEP_UNTIL(TIME)                                                   \
    std::this_thread::sleep_until(std::chrono::system_clock::now() + (TIME));

/**
 * @brief
 * @param NAME name存放的变量
 */
#define TX_THREAD_NAME(NAME)                                                   \
    {                                                                          \
        std::stringstream ss;                                                  \
        ss << (NAME);                                                          \
        std::string     name    = ss.str();                                    \
        std::thread::id this_id = std::this_thread::get_id();                  \
        pthread_setname_np(pthread_self(), name.c_str());                      \
    }

/**
 * @todo
 * @brief
 *
 */
#define TX_THREAD_NAME_DEFAULT                                                 \
    {                                                                          \
        std::stringstream ss;                                                  \
        ss << "Thread " << std::this_thread::get_id();                         \
        std::string name = ss.str();                                           \
        pthread_setname_np(pthread_self(), name.c_str());                      \
    }

#define TX_THREAD_NAME_DEFAULT_WITH_ID(ID)                                     \
    std::stringstream ss;                                                      \
    ss << "Thread " << (ID);                                                   \
    std::string name = ss.str();                                               \
    pthread_setname_np(pthread_self(), name.c_str());

#endif /* ENGINE_RUNTIME_CORE_BASE_MACRO */
