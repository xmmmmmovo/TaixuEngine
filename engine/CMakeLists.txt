set(ENGINE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ENGINE_ASSET_DIR "assets")
set(ENGINE_SHADER_DIR "shaders")

# accelerate the msvc project
if (MSVC)
    add_compile_options("/MP")
    add_compile_options("/utf-8")
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TaixuEngineEditor)
endif ()

# enables CCACHE support through the USE_CCACHE flag possible values are: YES, NO or equivalent
if (USE_CCACHE)
    CPMAddPackage(
            NAME ccache
            GITHUB_REPOSITORY "TheLartians/Ccache.cmake"
            VERSION 1.2.4
            OPTIONS
            "USE_CCACHE ${USE_CCACHE}"
    )
endif ()

# ------ third-party -------

# add Vulkan
include(FindVulkanLib)

# add DX11
include(FindDirectX11)

# add HarfBuzz
include(FindHarfBuzz)

# add freetype
include(FindFreetype)

# add glfw3
include(FindGlfw3)

# add glm
include(FindGLM)

# add stb
include(FindStb)

# add imgui
include(FindImgui)

# add fmt
include(FindFmt)

# add spdlog
include(FindSpdlog)

# add assimp
include(FindAssimp)

# add jsoncpp
include(FindSimdjson)

# add refl cpp
include(FindReflCpp)

# add magic enum
include(FindMagicEnum)

# add argparse
include(FindArgparse)

# add joltpyhsics
include(FindJoltPhysics)

find_package(Threads REQUIRED)

# ------- sub-directories --------

set(SHADER_COMPILE_TARGET TaixuShaderCompile)

set(SCRIPT_COMPILE_TARGET TaixuScriptLib)

set(INSTALL_DIR TaixuEngine)

add_subdirectory(shaders)
add_subdirectory(tools)

# editor and runtime
add_subdirectory(src/editor)
add_subdirectory(src/runtime)
add_subdirectory(src/script)
