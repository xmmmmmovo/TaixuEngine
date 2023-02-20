# imgui
CPMAddPackage(
        NAME imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG 345184330b438cb0aafcd6ff8ac1d3820f19b808
        DOWNLOAD_ONLY YES
)

if (imgui_ADDED)
    file(GLOB imgui_sources CONFIGURE_DEPENDS ${imgui_SOURCE_DIR}/*.cpp)
    file(GLOB imgui_impl CONFIGURE_DEPENDS
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h)

    file(GLOB imgui_ext_sources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/3rdparty/imgui/*.cpp)
    
    include_directories(${PROJECT_SOURCE_DIR}/3rdparty/imgui)

    add_library(imgui STATIC ${imgui_sources} ${imgui_impl} ${imgui_ext_sources})

    target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR}>)
    target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/3rdparty/imgui>)
    target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${Vulkan_INCLUDE_DIR}>)
    target_link_libraries(imgui PUBLIC glfw ${OGL})

    set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
    set_target_properties(imgui PROPERTIES FOLDER 3rdparty)
endif ()