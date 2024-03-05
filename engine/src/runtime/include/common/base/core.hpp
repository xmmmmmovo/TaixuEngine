//
// Created by xmmmmmovo on 11/19/2023.
//

#ifndef ENGINE_SRC_COMMON_BASE_COMMON_7AAF21E5E5DB40FEA443453F3D77703A
#define ENGINE_SRC_COMMON_BASE_COMMON_7AAF21E5E5DB40FEA443453F3D77703A

namespace taixu {

/**
 * @brief editor status enum
 */
enum class EnumEngineState : std::uint8_t {
    EDITORMODE, /// Editor mode
    PREVIEWMODE,/// play mode
    IDLEMODE,   /// idle mode, this mode will be used until project opened
    GAMEMODE    /// game mode, use for packed game
};

/**
 * @brief render API supported
 */
enum class EnumRenderAPI : std::uint8_t { VULKAN, DX11, DX12, NONE };

/**
 * @brief window API supported
 */
enum class EnumWindowAPI : std::uint8_t { GLFW, WINDOWSAPI, NONE };

/**
 * @brief window type supported
 */
enum class EnumWindowType : std::uint8_t {
    WINDOWED,
    FULLSCREEN,
    FULLSCREEN_DESKTOP
};

}// namespace taixu

#endif// ENGINE_SRC_COMMON_BASE_COMMON_7AAF21E5E5DB40FEA443453F3D77703A
