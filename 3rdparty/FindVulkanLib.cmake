# add Vulkan
find_package(Vulkan REQUIRED)

# TODO: test whether it works that imported by CPM
set(VOLK_STATIC_DEFINES_OPT "")
if(ANDROID)
    set(VOLK_STATIC_DEFINES_OPT VK_USE_PLATFORM_ANDROID_KHR)
elseif(X11_FOUND)
    set(VOLK_STATIC_DEFINES_OPT VK_USE_PLATFORM_XLIB_KHR)
elseif(WIN32)
    set(VOLK_STATIC_DEFINES_OPT VK_USE_PLATFORM_WIN32_KHR)
elseif(APPLE)
    set(VOLK_STATIC_DEFINES_OPT VK_USE_PLATFORM_MACOS_MVK)
endif()

# Volk
CPMAddPackage(
        NAME volk
        GITHUB_REPOSITORY zeux/volk
        GIT_TAG vulkan-sdk-1.3.268.0
        OPTIONS
        "VOLK_STATIC_DEFINES ${VOLK_STATIC_DEFINES_OPT}"
)

CPMAddPackage(
        NAME vulkan-memory-allocator
        GITHUB_REPOSITORY GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator
        GIT_TAG v3.0.1
        GIT_SHALLOW TRUE
        OPTIONS
        "VMA_BUILD_TESTS OFF"
        "VMA_BUILD_DOCS OFF"
        "VMA_BUILD_SAMPLES OFF"
)
