include(${PROJECT_SOURCE_DIR}/3rdparty/FindOpenGL.cmake)

set(GLAD_DIR ${PROJECT_SOURCE_DIR}/3rdparty/glad)
FILE(GLOB_RECURSE glad_headers CONFIGURE_DEPENDS ${GLAD_DIR}/include/*.h)
FILE(GLOB glad_sources ${GLAD_DIR}/src/*.c)
add_library(glad STATIC ${glad_headers} ${glad_sources})
target_include_directories(glad
    PUBLIC
    $<BUILD_INTERFACE:${GLAD_DIR}/include>
)