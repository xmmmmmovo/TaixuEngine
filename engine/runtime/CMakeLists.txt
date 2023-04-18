set(TARGET_NAME TaixuRuntime)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.inc")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

if (USE_PCH)
    target_precompile_headers(${TARGET_NAME} PRIVATE ${ENGINE_ROOT_DIR}/precompile/pch.hpp)
endif ()


target_link_libraries(${TARGET_NAME} glm glfw ${OGLLIB} ${FREETYPE_LIBS}
        glad imgui stb spdlog::spdlog assimp nlohmann_json::nlohmann_json refl-cpp::refl-cpp
        magic_enum::magic_enum freetype Jolt Threads::Threads)

add_dependencies(${TARGET_NAME} ${SHADER_COMPILE_TARGET})
target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/shaders/generated/cpp>)

target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/runtime>
        $<INSTALL_INTERFACE:include/${TARGET_NAME}>
)