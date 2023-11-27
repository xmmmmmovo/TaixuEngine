set(TARGET_NAME TaixuRuntime)

file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.inc")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

if (USE_PCH)
    target_precompile_headers(${TARGET_NAME} PRIVATE
            ${ENGINE_ROOT_DIR}/precompile/pch_std.hpp)
endif ()

add_dependencies(${TARGET_NAME} ${COMMON_COMPILE_TARGET})

target_link_libraries(${TARGET_NAME} PUBLIC ${COMMON_COMPILE_TARGET})

target_link_libraries(${TARGET_NAME} PUBLIC Threads::Threads freetype)
target_link_libraries(${TARGET_NAME} PUBLIC Jolt stb)
target_link_libraries(${TARGET_NAME} PUBLIC simdjson magic_enum::magic_enum)
target_link_libraries(${TARGET_NAME} PUBLIC refl-cpp::refl-cpp assimp)

# public link
target_link_libraries(${TARGET_NAME} PUBLIC glm imgui argparse)

if (USE_VULKAN)
    add_dependencies(${TARGET_NAME} ${SHADER_COMPILE_TARGET}_VK)

    target_link_libraries(${TARGET_NAME} PUBLIC glfw)
    target_link_libraries(${TARGET_NAME} PRIVATE Vulkan::Vulkan volk VulkanMemoryAllocator)
    target_include_directories(${TARGET_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
endif ()

target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/shaders/generated/cpp>)

target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/src/runtime>
        $<INSTALL_INTERFACE:include/${INSTALL_DIR}/${TARGET_NAME}>
)