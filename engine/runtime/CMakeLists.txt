set(TARGET_NAME TaixuEngineRuntime)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME} Vulkan::Vulkan glm glfw imgui stb spdlog::spdlog)

add_dependencies(${TARGET_NAME} ${SHADER_COMPILE_TARGET})
target_include_directories(
  ${TARGET_NAME}
  PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/shaders/generated/cpp>)
