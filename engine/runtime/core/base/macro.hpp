#ifndef ENGINE_RUNTIME_CORE_BASE_MACRO
#define ENGINE_RUNTIME_CORE_BASE_MACRO

#include <string_view>

namespace taixu {
constexpr char         OPENGL_VERSION[]     = "#version 410";
constexpr std::int32_t OPENGL_MAJOR_VERSION = 4;
constexpr std::int32_t OPENGL_MINOR_VERSION = 1;

// Define status enum  

enum class status {
    OK,                     //access allowed
    PERMISSION_FAILED,      //access permission failed
    NO_SUCH_FILE_FAILED     //cannot find file path

};

}// namespace taixu::core


#endif /* ENGINE_RUNTIME_CORE_BASE_MACRO */
