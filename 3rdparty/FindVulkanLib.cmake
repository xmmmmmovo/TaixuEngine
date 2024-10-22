# add Vulkan
find_package(Vulkan REQUIRED)

CPMAddPackage(
    NAME vulkan-memory-allocator
    GITHUB_REPOSITORY GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator
    GIT_TAG v3.1.0
    OPTIONS
    "VMA_BUILD_TESTS OFF"
    "VMA_BUILD_DOCS OFF"
    "VMA_BUILD_SAMPLES OFF"
)
