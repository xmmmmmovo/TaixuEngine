
set(ENGINE_ASSET_DIR "/assets")

# accelerate the msvc project
if(MSVC)
    add_compile_options("/MP")
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TaixuEngineEditor)
endif()

# add glsl validator
set(glslangValidator_executable ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE})

# ------ third-party -------

# add Vulkan
find_package(Vulkan REQUIRED)

#add glfw3
include(../3rdparty/FindGlfw3.cmake)

# add glm
include(../3rdparty/FindGLM.cmake)

#add GroupSourcesByFolder
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
add_subdirectory(shaders)

# editor and runtime
add_subdirectory(editor)
add_subdirectory(runtime)