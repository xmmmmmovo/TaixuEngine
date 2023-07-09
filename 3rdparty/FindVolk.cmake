include(${PROJECT_SOURCE_DIR}/3rdparty/FindVulkan.cmake)

# Volk
CPMAddPackage(
        NAME volk
        GITHUB_REPOSITORY zeux/volk
        GIT_TAG sdk-1.3.236.0
        GIT_SHALLOW TRUE
)

if (WIN32)
    set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
elseif (UNIX)
    if (APPLE)
        set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_MACOS_MVK)
    else ()
        set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
    endif ()
endif ()
