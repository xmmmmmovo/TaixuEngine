set(TARGET_NAME TaixuRuntime)

include(SourceUtils)

FIND_GLOB_RECURSE(SOURCE_FILES
        "source/common/*.cpp"
        "source/common/*.hpp"
        "source/engine/*.cpp"
        "source/engine/*.hpp"
        "source/gameplay/*.cpp"
        "source/gameplay/*.hpp"
        "source/management/*.cpp"
        "source/management/*.hpp"
        "source/resource/*.cpp"
        "source/resource/*.hpp"
)

# Adapt different platforms
FIND_GLOB_RECURSE(PLATFORM_FILES
        "source/platform/os/*.cpp"
        "source/platform/os/*.hpp"
)

# adapt vulkan
if(USE_VULKAN)
        FIND_GLOB_RECURSE(PLATFORM_VK_FILES
                "source/platform/vulkan/*.cpp"
                "source/platform/vulkan/*.hpp"
        )
        list(APPEND PLATFORM_FILES ${PLATFORM_VK_FILES})
endif()

# adapt os
if(MSVC)
        FIND_GLOB_RECURSE(PLATFORM_WIN_FILES
                "source/platform/windows/*.cpp"
                "source/platform/windows/*.hpp"
        )
        list(APPEND PLATFORM_FILES ${PLATFORM_WIN_FILES})
elseif(APPLE)
        FIND_GLOB_RECURSE(PLATFORM_DARWIN_FILES
                "source/platform/darwin/*.cpp"
                "source/platform/darwin/*.hpp"
        )
        list(APPEND PLATFORM_FILES ${PLATFORM_DARWIN_FILES})
else()
        FIND_GLOB_RECURSE(PLATFORM_LINUX_FILES
                "source/platform/linux/*.cpp"
                "source/platform/linux/*.hpp"
        )
        list(APPEND PLATFORM_FILES ${PLATFORM_LINUX_FILES})
endif()

FIND_GLOB_RECURSE(HEADER_FILES "include/*.hpp")

set(SOURCE_FILES ${SOURCE_FILES} ${PLATFORM_FILES} ${HEADER_FILES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCE_FILES} ${PLATFORM_FILES} ${HEADER_FILES})

add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set(PCH_FILES "${PCH_DIR}/pch_std.hpp" "${PCH_DIR}/pch_runtime.hpp")

# add options
set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 23)

if(MSVC AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${TARGET_NAME} PRIVATE "/DEBUG" "/Zf" "/nologo" "/W3" "/Od")
endif()

if(WARNINGS)
        target_compile_definitions(${TARGET_NAME} PRIVATE TAIXU_WARNINGS_DEF)
endif()

# accelerate the msvc project
if(MSVC)
        target_compile_options(${TARGET_NAME} PRIVATE "/MP" "/utf-8")
        target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE _UNICODE)
endif()

# public link
target_link_libraries(${TARGET_NAME} PRIVATE stb)
target_link_libraries(${TARGET_NAME} PRIVATE simdjson Threads::Threads freetype glfw)
target_link_libraries(${TARGET_NAME} PRIVATE assimp)
target_link_libraries(${TARGET_NAME} PRIVATE Jolt argparse)

target_link_libraries(${TARGET_NAME} PUBLIC mimalloc-static)
target_link_libraries(${TARGET_NAME} PUBLIC refl-cpp::refl-cpp imgui
        spdlog::spdlog fmt::fmt magic_enum::magic_enum glm)

if(USE_VULKAN)
        add_dependencies(${TARGET_NAME} ${SHADER_COMPILE_TARGET}_VK)

        list(APPEND PCH_FILES "${PCH_DIR}/pch_vulkan.hpp")
        target_link_libraries(${TARGET_NAME} PUBLIC Vulkan::Vulkan volk VulkanMemoryAllocator)
        target_include_directories(${TARGET_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
endif()

if(USE_PCH)
        target_precompile_headers(${TARGET_NAME} PRIVATE ${PCH_FILES})
endif()

target_include_directories(
        ${TARGET_NAME}
        PRIVATE $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/shaders/generated/cpp>)
target_include_directories(
        ${TARGET_NAME}
        PRIVATE $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/src/runtime/source>)

target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/src/runtime/include>
        $<INSTALL_INTERFACE:include/${INSTALL_DIR}/${TARGET_NAME}>
)
