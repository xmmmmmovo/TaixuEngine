# add Vulkan
find_package(Vulkan REQUIRED)

# TODO: test whether it works that imported by CPM
if (WIN32)
    set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
elseif (UNIX)
    if (APPLE)
        set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_MACOS_MVK)
    else ()
        set(VOLK_STATIC_DEFINES VK_USE_PLATFORM_WIN32_KHR)
    endif ()
endif ()

# Volk
CPMAddPackage(
        NAME volk
        GITHUB_REPOSITORY zeux/volk
        GIT_TAG vulkan-sdk-1.3.268.0
        GIT_SHALLOW TRUE
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
