#ifndef ENGINE_RUNTIME_CORE_BASE_MACRO
#define ENGINE_RUNTIME_CORE_BASE_MACRO

namespace taixu {

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

/**
 * @brief Define Opengl version
 */
constexpr char         OPENGL_VERSION[]     = "#version 410";
/**
 * @brief Define Opengl major version
 */
constexpr std::int32_t OPENGL_MAJOR_VERSION = 4;
/**
 * @brief Define Opengl minor version
 */
constexpr std::int32_t OPENGL_MINOR_VERSION = 1;

/**
 * @brief status enum
 */
enum class Status {
    OK,                 // access allowed
    PERMISSION_FAILED,  // access permission failed
    NO_SUCH_FILE_FAILED,// cannot find file path

    NO_OPEN_PROJECT,    // no project opened

    // RENDER STATUS CODES

    // END RENDER STATUS CODES
};

/**
 * @brief editor status enum
 */
enum class EngineState {
    EDITORMODE,  /*Editor mode*/
    PREVIEWMODE, /*play mode*/
    IDLEMODE,    /*idle mode, this mode will be used until project opened*/
    GAMEMODE
};


}// namespace taixu

#endif /* ENGINE_RUNTIME_CORE_BASE_MACRO */
