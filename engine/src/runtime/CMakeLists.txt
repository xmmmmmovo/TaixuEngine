set(TARGET_NAME TaixuRuntime)

include(SourceUtils)

set(COMMON_TARGET "TaixuCommonLib")
set(ENGINE_TARGET "TaixuEngineRuntimeLib")
set(GAMEPLAY_TARGET "TaixuGameplayRuntimeLib")

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

FIND_GLOB_RECURSE(PLATFORM_FILES "source/platform/*.cpp")

FIND_GLOB_RECURSE(HEADER_FILES "include/*.hpp")

set(SOURCE_FILES ${SOURCE_FILES} ${PLATFORM_FILES} ${HEADER_FILES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCE_FILES})

add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

set(PCH_FILES "${PCH_DIR}/pch_std.hpp" "${PCH_DIR}/pch_runtime.hpp")

# public link
target_link_libraries(${TARGET_NAME} PRIVATE stb)
target_link_libraries(${TARGET_NAME} PRIVATE simdjson Threads::Threads freetype glfw)
target_link_libraries(${TARGET_NAME} PRIVATE refl-cpp::refl-cpp assimp)
target_link_libraries(${TARGET_NAME} PRIVATE Jolt argparse)

target_link_libraries(${TARGET_NAME} PUBLIC imgui spdlog::spdlog fmt::fmt magic_enum::magic_enum glm)

if (USE_VULKAN)
    add_dependencies(${TARGET_NAME} ${SHADER_COMPILE_TARGET}_VK)

    list(APPEND PCH_FILES "${PCH_DIR}/pch_vulkan.hpp")
    target_link_libraries(${TARGET_NAME} PRIVATE Vulkan::Vulkan volk VulkanMemoryAllocator)
    target_include_directories(${TARGET_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
endif ()

if (USE_DX11)
    add_dependencies(${TARGET_NAME} ${SHADER_COMPILE_TARGET}_DX11)

    list(APPEND PCH_FILES "${PCH_DIR}/pch_dx11.hpp")
    target_link_libraries(${TARGET_NAME} PRIVATE ${DX11_LIB})
endif ()

if (USE_PCH)
    target_precompile_headers(${TARGET_NAME} PRIVATE ${PCH_FILES})
endif ()

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