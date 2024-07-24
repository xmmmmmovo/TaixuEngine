# imgui
CPMAddPackage(
    NAME imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG 8048b52498a9bf2a9f87b080d43b0bfd7a5d51d8
    DOWNLOAD_ONLY YES
)

if(imgui_ADDED)
    file(GLOB imgui_sources CONFIGURE_DEPENDS ${imgui_SOURCE_DIR}/*.cpp)

    file(GLOB imgui_impl CONFIGURE_DEPENDS
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h
    )

    if(USE_VULKAN)
        # append file to imgui_impl
        list(APPEND imgui_impl ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp)
        list(APPEND imgui_impl ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.h)
    endif()

    if(USE_DX11)
        # append file to imgui_impl
        list(APPEND imgui_impl ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp)
        list(APPEND imgui_impl ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.h)
    endif()

    set(ADDON_PATH ${PROJECT_SOURCE_DIR}/3rdparty/imgui_addons)

    file(GLOB_RECURSE imgui_ext_sources CONFIGURE_DEPENDS ${ADDON_PATH}/*.cpp)

    add_library(imgui STATIC ${imgui_sources} ${imgui_impl} ${imgui_ext_sources})
    set_target_properties(imgui PROPERTIES CXX_STANDARD 23)

    target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>)
    target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${ADDON_PATH}>)

    target_link_libraries(imgui PUBLIC freetype glfw)

    if(USE_VULKAN)
        target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>)
        target_link_libraries(imgui PUBLIC Vulkan::Vulkan)
    endif()

    if(USE_DX11)
        target_link_libraries(imgui PUBLIC ${DX11_LIB})
    endif()

    set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(imgui PROPERTIES FOLDER 3rdparty)
endif()
