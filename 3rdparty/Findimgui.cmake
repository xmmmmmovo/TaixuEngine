set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/3rdparty/imgui-1.89.2)

file(GLOB IMGUI_SOURCES ${IMGUI_DIR}/*.cpp)
file(GLOB IMGUI_HEADERS ${IMGUI_DIR}/*.h)

set(IMGUI_BACKENDS_DIR ${IMGUI_DIR}/backends)

set(IMGUI_BACKEND_SOURCES
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_vulkan.cpp)
set(IMGUI_BACKEND_HEADERS
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.h
    ${IMGUI_BACKENDS_DIR}/imgui_impl_vulkan.h)

add_library(imgui STATIC
    ${IMGUI_HEADERS} ${IMGUI_SOURCES}
    ${IMGUI_BACKEND_HEADERS} ${IMGUI_BACKEND_SOURCES})

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_BACKENDS_DIR}
    ${Vulkan_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    )
target_link_libraries(imgui PUBLIC glfw ${VULKAN_LIB})

set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(imgui PROPERTIES FOLDER 3rdparty)