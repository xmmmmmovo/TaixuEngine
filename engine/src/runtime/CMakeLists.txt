set(TARGET_NAME TaixuRuntime)

macro(FIND_GLOB_RECURSE OUT_VAR)
    file(GLOB_RECURSE ${OUT_VAR} ${ARGN})
endmacro()

FIND_GLOB_RECURSE(SOURCE_FILES
        "source/common/*.cpp"
        "source/engine/*.cpp"
        "source/gameplay/*.cpp"
        "source/management/*.cpp"
        "source/resource/*.cpp")

FIND_GLOB_RECURSE(PLATFORM_FILES "source/platform/*.cpp")

set(SOURCE_FILES ${SOURCE_FILES} ${PLATFORM_FILES})

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

    target_link_libraries(${TARGET_NAME} PRIVATE d3d11.lib dxgi.lib dxguid.lib)
endif ()

target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/shaders/generated/cpp>)

target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/src/runtime/include>
        $<INSTALL_INTERFACE:include/${INSTALL_DIR}/${TARGET_NAME}>
)