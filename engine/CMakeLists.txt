set(ENGINE_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ENGINE_ASSET_DIR "assets")
set(ENGINE_SHADER_DIR "shaders")

# accelerate the msvc project
if (MSVC)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TaixuEngineEditor)
endif ()

# ------ third-party -------

if (USE_VULKAN)
    # add Vulkan
    include(FindVulkanLib)
endif ()

# add HarfBuzz
include(FindHarfBuzz)
# add freetype
include(FindFreetype)
# add glfw3
include(FindGLFW3)
# add glm
include(FindGLM)
# add stb
include(FindStb)
# add imgui
include(FindImgui)
# add fmt
include(FindFmt)
# add quill
include(FindQuill)
# add assimp
include(FindAssimp)
# add magic enum
include(FindMagicEnum)
# add argparse
include(FindArgparse)
# add joltpyhsics
include(FindJoltPhysics)
# add mimalloc
include(FindMimalloc)
# add reflcpp
include(FindReflcpp)
# add taskflow
include(FindTaskflow)

# add threads
find_package(Threads REQUIRED)

# ------- sub-directories --------

set(SHADER_COMPILE_TARGET TaixuShaderCompile)
set(INSTALL_DIR TaixuEngine)

set(PCH_DIR ${ENGINE_ROOT_DIR}/precompile)

add_subdirectory(shaders)
add_subdirectory(tools)

# editor and runtime
add_subdirectory(src/editor)
add_subdirectory(src/runtime)
