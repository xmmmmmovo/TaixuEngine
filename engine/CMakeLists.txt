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
# include(../3rdparty/FindVolk.cmake)
include(../3rdparty/FindGlad.cmake)

# add freetype
# include(../3rdparty/FindFreetype.cmake)

# add glfw3
include(../3rdparty/FindGlfw3.cmake)

# add glm
include(../3rdparty/FindGLM.cmake)

# add GroupSourcesByFolder
include(../3rdparty/FindGroupSourcesByFolder.cmake)

# add stb
include(../3rdparty/FindStb.cmake)

# add imgui
include(../3rdparty/Findimgui.cmake)

# add fmt
include(../3rdparty/Findfmt.cmake)

# add spdlog
include(../3rdparty/FindSpdlog.cmake)

# add assimp
include(../3rdparty/FindAssimp.cmake)

# add yaml
include(../3rdparty/FindYamlCpp.cmake)

# add jsoncpp
#include(../3rdparty/FindJsoncpp.cmake)

# ------- sub-directories --------

# for SPIR_V
set(SPIR_V_ENABLE OFF)

# shaders
# add glsl validator
set(glslangValidator_executable ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE})
set(SHADER_COMPILE_TARGET TaixuShaderCompile)
add_subdirectory(shaders)

# editor and runtime
add_subdirectory(editor)
add_subdirectory(runtime)