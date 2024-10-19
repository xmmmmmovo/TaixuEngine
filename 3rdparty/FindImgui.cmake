# imgui
CPMAddPackage(
    NAME imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG c71e4e8c7cb9b42b460bbaedfa4bc443f885b05b
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

    set(ADDON_PATH ${PROJECT_SOURCE_DIR}/3rdparty/imgui_addons)

    file(GLOB_RECURSE imgui_ext_sources CONFIGURE_DEPENDS ${ADDON_PATH}/*.cpp)

    add_library(imgui STATIC ${imgui_sources} ${imgui_impl} ${imgui_ext_sources})
    set_target_properties(imgui PROPERTIES CXX_STANDARD 20)

    target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>)
    target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${ADDON_PATH}>)

    target_link_libraries(imgui PRIVATE freetype glfw)

    if(USE_VULKAN)
        target_link_libraries(imgui PRIVATE Vulkan::Vulkan)
    endif()

    set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(imgui PROPERTIES FOLDER 3rdparty)
endif()
