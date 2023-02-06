#add glfw3
include(../3rdparty/FindGlfw3.cmake)

# add glm
include(../3rdparty/FindGLM.cmake)

# add Vulkan
find_package(Vulkan REQUIRED)

# enables CCACHE support through the USE_CCACHE flag possible values are: YES, NO or equivalent
if (USE_CCACHE)
    include(../3rdparty/FindCCache.cmake)
endif ()

add_subdirectory(editor)