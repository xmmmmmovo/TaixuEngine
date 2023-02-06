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

# enables CCACHE support through the USE_CCACHE flag possible values are: YES, NO or equivalent
if (USE_CCACHE)
    include(../3rdparty/FindCCache.cmake)
endif ()

add_subdirectory(editor)