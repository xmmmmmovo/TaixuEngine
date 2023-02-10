set(ENGINE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ENGINE_ASSET_DIR "assets")

# accelerate the msvc project
if(MSVC)
    add_compile_options("/MP")
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TaixuEngineEditor)
endif()

# ------ third-party -------

# add Vulkan
# include(../3rdparty/FindVolk.cmake)
include(../3rdparty/FindGlad.cmake)

# add freetype
include(../3rdparty/FindFreetype.cmake)

# add glfw3
include(../3rdparty/FindGlfw3.cmake)

# add glm
include(../3rdparty/FindGLM.cmake)

# add GroupSourcesByFolder
include(../3rdparty/FindGroupSourcesByFolder.cmake)

# add imgui
include(../3rdparty/Findimgui.cmake)

# add stb
include(../3rdparty/FindStb.cmake)

# add fmt
include(../3rdparty/Findfmt.cmake)

# add spdlog
include(../3rdparty/FindSpdlog.cmake)

# ------- sub-directories --------

# shaders
# add glsl validator
set(glslangValidator_executable ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE})
set(SHADER_COMPILE_TARGET TaixuShaderCompile)
add_subdirectory(shaders)

# editor and runtime
add_subdirectory(editor)
add_subdirectory(runtime)