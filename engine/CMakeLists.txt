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
include(../3rdparty/FindVulkan.cmake)

# add HarfBuzz
include(../3rdparty/FindHarfBuzz.cmake)

# add freetype
include(../3rdparty/FindFreetype.cmake)

# add glfw3
include(../3rdparty/FindGlfw3.cmake)

# add glm
include(../3rdparty/FindGLM.cmake)

# add stb
include(../3rdparty/FindStb.cmake)

# add imgui
include(../3rdparty/FindImgui.cmake)

# add fmt
include(../3rdparty/FindFmt.cmake)

# add spdlog
include(../3rdparty/FindSpdlog.cmake)

# add assimp
include(../3rdparty/FindAssimp.cmake)

# add jsoncpp
include(../3rdparty/FindJsoncpp.cmake)

# add refl cpp
include(../3rdparty/FindReflCpp.cmake)

# add magic enum
include(../3rdparty/FindMagicEnum.cmake)

# add argparse
include(../3rdparty/FindArgparse.cmake)

# add joltpyhsics
include(../3rdparty/FindJoltPhysics.cmake)

find_package(Threads REQUIRED)

# ------- sub-directories --------

# shaders
# add glsl compiler
if (USE_VULKAN)
    set(GLSLANG_VALIDATOR_EXECUTABLE ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE})
    if (NOT GLSLANG_VALIDATOR_EXECUTABLE)
        find_program(GLSLC_EXECUTABLE glslc
                PATHS "${TAIXUENGINE_ROOT_DIR}/3rd_party/bin")
        if (NOT GLSLC_EXECUTABLE)
            message(FATAL_ERROR "glsl compiler not found!")
        else ()
            message("glsl ${GLSLC_EXECUTABLE}")
            set(GLSL_COMPILER ${GLSLC_EXECUTABLE})
        endif ()
    else ()
        message("glsl ${GLSLANG_VALIDATOR_EXECUTABLE}")
        set(GLSL_COMPILER ${GLSLANG_VALIDATOR_EXECUTABLE})
    endif ()
endif ()

set(SHADER_COMPILE_TARGET TaixuShaderCompile)

set(COMMON_COMPILE_TARGET TaixuCommonLib)
set(SCRIPT_COMPILE_TARGET TaixuScriptLib)

add_subdirectory(shaders)
add_subdirectory(tools)

# editor and runtime
add_subdirectory(src/editor)
add_subdirectory(src/common)
add_subdirectory(src/runtime)
add_subdirectory(src/script)
