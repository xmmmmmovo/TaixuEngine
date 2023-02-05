# add glm
include(../cmake/FindGLM.cmake)

find_package(glfw3 CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

# enables CCACHE support through the USE_CCACHE flag possible values are: YES, NO or equivalent
if (USE_CCACHE)
    include(../cmake/FindCCache.cmake)
endif ()

add_subdirectory(editor)