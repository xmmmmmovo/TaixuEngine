set(TARGET_NAME TaixuRuntime)

macro(FIND_GLOB_RECURSE OUT_VAR)
    file(GLOB_RECURSE ${OUT_VAR} ${ARGN})
endmacro()

FIND_GLOB_RECURSE(COMMON_HEADERS "common/*.hpp")
FIND_GLOB_RECURSE(COMMON_FILES "common/*.cpp")
FIND_GLOB_RECURSE(ENGINE_HEADERS "engine/*.hpp")
FIND_GLOB_RECURSE(ENGINE_FILES "engine/*.cpp")
FIND_GLOB_RECURSE(GAMEPLAY_HEADERS "gameplay/*.hpp")
FIND_GLOB_RECURSE(GAMEPLAY_FILES "gameplay/*.cpp")
FIND_GLOB_RECURSE(MANAGEMENT_HEADERS "management/*.hpp")
FIND_GLOB_RECURSE(MANAGEMENT_FILES "management/*.cpp")
FIND_GLOB_RECURSE(RESOURCE_HEADERS "resource/*.hpp")
FIND_GLOB_RECURSE(RESOURCE_FILES "resource/*.cpp")

FIND_GLOB_RECURSE(PLATFORM_HEADERS "platform/*.hpp")
FIND_GLOB_RECURSE(PLATFORM_FILES "platform/*.cpp")

set(HEADER_FILES ${COMMON_HEADERS} ${ENGINE_HEADERS} ${GAMEPLAY_HEADERS}
        ${MANAGEMENT_HEADERS} ${RESOURCE_HEADERS} ${PLATFORM_HEADERS})
set(SOURCE_FILES ${COMMON_FILES} ${ENGINE_FILES} ${GAMEPLAY_FILES}
        ${MANAGEMENT_FILES} ${RESOURCE_FILES} ${PLATFORM_FILES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

if (USE_PCH)
    target_precompile_headers(${TARGET_NAME} PRIVATE
            ${ENGINE_ROOT_DIR}/precompile/pch_std.hpp)
endif ()

# public link
target_link_libraries(${TARGET_NAME} PUBLIC magic_enum::magic_enum stb)
target_link_libraries(${TARGET_NAME} PUBLIC simdjson Threads::Threads freetype glfw)
target_link_libraries(${TARGET_NAME} PUBLIC Jolt)
target_link_libraries(${TARGET_NAME} PUBLIC refl-cpp::refl-cpp assimp)
target_link_libraries(${TARGET_NAME} PUBLIC glm imgui argparse spdlog::spdlog fmt::fmt)

if (USE_VULKAN)
    add_dependencies(${TARGET_NAME} ${SHADER_COMPILE_TARGET}_VK)

    target_link_libraries(${TARGET_NAME} PRIVATE Vulkan::Vulkan volk VulkanMemoryAllocator)
    target_include_directories(${TARGET_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
endif ()

if (USE_DX11)
    add_dependencies(${TARGET_NAME} ${SHADER_COMPILE_TARGET}_DX11)

    target_link_libraries(${TARGET_NAME} PRIVATE d3d11.lib dxgi.lib dxguid.lib
            D3DCompiler.lib d2d1.lib dwrite.lib winmm.lib)
endif ()

target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/shaders/generated/cpp>)

target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/src/runtime>
        $<INSTALL_INTERFACE:include/${INSTALL_DIR}/${TARGET_NAME}>
)