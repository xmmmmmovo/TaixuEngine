//
// Created by xmmmmmovo on 11/19/2023.
//

#ifndef ENGINE_SRC_COMMON_BASE_COMMON_7AAF21E5E5DB40FEA443453F3D77703A
#define ENGINE_SRC_COMMON_BASE_COMMON_7AAF21E5E5DB40FEA443453F3D77703A

namespace taixu {

/**
 * @brief editor status enum
 */
enum class EngineState : std::uint8_t {
    EDITORMODE, /// Editor mode
    PREVIEWMODE,/// play mode
    IDLEMODE,   /// idle mode, this mode will be used until project opened
    GAMEMODE    /// game mode, use for packed game
};

/**
 * @brief window API supported
 */
enum class WindowAPI : std::uint8_t { GLFW, EMSCRIPTEN, NONE };

/**
 * @brief render API supported
 */
enum class RenderAPI : std::uint8_t { VULKAN, WGPU };

/**
 * @brief window type supported
 */
enum class WindowType : std::uint8_t { WINDOWED, FULLSCREEN, FULLSCREEN_DESKTOP };

/**
 * @brief Whole return code / status code enum class.
 */
enum class RetCode : std::uint32_t {
    SUCCESS       = 0,// success
    UNKNOWN_ERROR = 1,// unknow error
    UNIMPL_ERROR  = 2,// unimplement error

    COMMON_ERROR = (1 << 10),

    GAMEPLAY_ERROR = (1 << 10) * 2,

    MANAGEMENT_ERROR = (1 << 10) * 3,
    UNSUPPORTED_VULKAN_ERROR,
    VULKAN_INIT_ERROR,
    VULKAN_INSTANCE_CREATE_ERROR,
    VULKAN_DEVICE_CREATE_ERROR,

    PLATFORM_ERROR = (1 << 10) * 4,

    RESOURCE_ERROR = (1 << 10) * 5,
};

}// namespace taixu

#endif// ENGINE_SRC_COMMON_BASE_COMMON_7AAF21E5E5DB40FEA443453F3D77703A
