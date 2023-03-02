#ifndef ENGINE_RUNTIME_CORE_BASE_MACRO
#define ENGINE_RUNTIME_CORE_BASE_MACRO

#include <string_view>

namespace taixu {

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

// Define status enum
enum class Status {
    OK,                //access allowed
    PERMISSION_FAILED, //access permission failed
    NO_SUCH_FILE_FAILED//cannot find file path
};

// Define engine mode enum
enum class EngineMode {
    EDITOR,//editor mode
    GAME   //game mode
};

template<typename... Args>
using callback = std::function<void(Args...)>;//callback function

}// namespace taixu


#endif /* ENGINE_RUNTIME_CORE_BASE_MACRO */
