#ifndef ENGINE_RUNTIME_CORE_BASE_MACRO
#define ENGINE_RUNTIME_CORE_BASE_MACRO

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
    OK,                 //access allowed
    PERMISSION_FAILED,  //access permission failed
    NO_SUCH_FILE_FAILED,//cannot find file path

    NO_OPEN_PROJECT,//no project opened

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
