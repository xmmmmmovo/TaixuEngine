# imgui
CPMAddPackage(
        NAME imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG 345184330b438cb0aafcd6ff8ac1d3820f19b808
        GIT_SHALLOW TRUE
        DOWNLOAD_ONLY YES
)

if (imgui_ADDED)
    file(GLOB imgui_sources CONFIGURE_DEPENDS ${imgui_SOURCE_DIR}/*.cpp)

    file(GLOB imgui_impl CONFIGURE_DEPENDS
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h
    )

    if (USE_VULKAN)
        # append file to imgui_impl
        list(APPEND imgui_impl ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp)
        list(APPEND imgui_impl ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.h)
    endif ()

    file(GLOB imgui_ext_sources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/3rdparty/imgui/*.cpp)

    add_library(imgui STATIC ${imgui_sources} ${imgui_impl} ${imgui_ext_sources})

    target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>)
    target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/3rdparty/imgui>)

    target_link_libraries(imgui PUBLIC glfw)

    if (USE_VULKAN)
        target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>)
        target_link_libraries(imgui PUBLIC Vulkan::Vulkan)
    endif ()

    set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(imgui PROPERTIES FOLDER 3rdparty)
endif ()