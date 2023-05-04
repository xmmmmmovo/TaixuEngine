set(TARGET_NAME TaixuEngineEditor)

file(GLOB_RECURSE EDITOR_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE EDITOR_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB EDITOR_RESOURCE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/res/TaixuEditor.rc)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${EDITOR_HEADERS} ${EDITOR_SOURCES} ${EDITOR_RESOURCE})

add_executable(${TARGET_NAME} ${EDITOR_HEADERS} ${EDITOR_SOURCES} ${EDITOR_RESOURCE})

target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME ${TARGET_NAME})

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "EngineShader")

# 使用MSVC标准
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX->")

# link libraries
target_link_libraries(${TARGET_NAME} PRIVATE TaixuRuntime)
target_link_libraries(${TARGET_NAME} PRIVATE argparse)

if (USE_PCH)
    target_precompile_headers(${TARGET_NAME} PRIVATE ${ENGINE_ROOT_DIR}/precompile/pch.hpp)
endif ()

if ("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" STREQUAL "")
    set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
else ()
    set(OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif ()

if (MSVC)
    set(OUTPUT_DIR ${OUTPUT_DIR}/Debug)
endif (MSVC)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -DENGINE_ROOT_DIR=${ENGINE_ROOT_DIR} -DOUTPUT_DIR=${OUTPUT_DIR} -P ${PROJECT_SOURCE_DIR}/cmake/MoveResourceDirs.cmake
        )

if (${CMAKE_BUILD_TYPE})
    message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
    if (${CMAKE_BUILD_TYPE} NOT STREQUAL "Debug")
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory "${BINARY_ROOT_DIR}"
                COMMAND ${CMAKE_COMMAND} -E copy "${ENGINE_ROOT_DIR}/${TARGET_NAME}.json" "${BINARY_ROOT_DIR}"
                COMMAND ${CMAKE_COMMAND} -E copy "${OUTPUT_DIR}/${TARGET_NAME}" "${BINARY_ROOT_DIR}"
                COMMAND ${CMAKE_COMMAND} -E copy "${OUTPUT_DIR}/imgui.ini" "${BINARY_ROOT_DIR}"
                COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/res" "${BINARY_ROOT_DIR}/res"
                COMMAND ${CMAKE_COMMAND} -E remove_directory "${BINARY_ROOT_DIR}/${ENGINE_ASSET_DIR}"
                COMMAND ${CMAKE_COMMAND} -E copy_directory "${ENGINE_ROOT_DIR}/${ENGINE_ASSET_DIR}" "${BINARY_ROOT_DIR}/${ENGINE_ASSET_DIR}"
                )
    endif ()
endif ()
