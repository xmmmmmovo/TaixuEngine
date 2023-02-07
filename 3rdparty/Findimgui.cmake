#imgui
CPMAddPackage(
    NAME imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    VERSION 1.89.2
    DOWNLOAD_ONLY YES
)

if(imgui_ADDED)
    file(GLOB imgui_sources CONFIGURE_DEPENDS ${imgui_SOURCE_DIR}/*.cpp)
    file(GLOB imgui_impl CONFIGURE_DEPENDS  
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.h)

    add_library(imgui STATIC ${imgui_sources} ${imgui_impl})

    target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>)
    target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>)
    target_link_libraries(imgui PUBLIC glfw ${VULKAN_LIB})

    set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(imgui PROPERTIES FOLDER 3rdparty)
endif()