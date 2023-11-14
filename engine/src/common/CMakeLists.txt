set(TARGET_NAME ${COMMON_COMPILE_TARGET})

file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.inc")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

add_library(${TARGET_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${TARGET_NAME} PUBLIC glm)

if (USE_PCH)
    target_precompile_headers(${TARGET_NAME} PRIVATE ${ENGINE_ROOT_DIR}/precompile/pch_common.hpp)
endif ()

target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/src>
        $<INSTALL_INTERFACE:include/${TARGET_NAME}>
)