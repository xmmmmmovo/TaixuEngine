set(TARGET_NAME TaixuEngineEditor)

file(GLOB_RECURSE EDITOR_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE EDITOR_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB EDITOR_RESOURCE CONFIGURE_DEPENDS res/TaixuEditor.rc)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${EDITOR_HEADERS} ${EDITOR_SOURCES} ${EDITOR_RESOURCE})

add_executable(${TARGET_NAME} ${EDITOR_HEADERS} ${EDITOR_SOURCES} ${EDITOR_RESOURCE})

target_include_directories(${TARGET_NAME} PRIVATE $<BUILD_INTERFACE:${ENGINE_ROOT_DIR}/src/editor>)

# set standard and output name
set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 23 OUTPUT_NAME ${TARGET_NAME})
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "EngineEditor")

# 使用MSVC标准
target_compile_options(${TARGET_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/WX->")

# accelerate the msvc project
if(MSVC)
    target_compile_options(${TARGET_NAME} PRIVATE "/MP" "/utf-8")
    target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE _UNICODE)
endif()

if(WARNINGS)
    target_compile_definitions(${TARGET_NAME} PRIVATE TAIXU_WARNINGS_DEF)
endif()

# link libraries
target_link_libraries(${TARGET_NAME} PRIVATE TaixuRuntime)
target_link_libraries(${TARGET_NAME} PRIVATE argparse glm magic_enum::magic_enum)

if(USE_PCH)
    target_precompile_headers(${TARGET_NAME} PRIVATE ${PCH_DIR}/pch_std.hpp ${PCH_DIR}/pch_editor.hpp)
endif()

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -DSRC_PATH="${ENGINE_ROOT_DIR}/src/editor/imgui.ini" -DDEST_PATH="${OUTPUT_DIR}" -P ${TAIXUENGINE_ROOT_DIR}/cmake/MoveByPath.cmake
    COMMAND ${CMAKE_COMMAND} -DSRC_PATH="${ENGINE_ROOT_DIR}/assets" -DDEST_PATH="${OUTPUT_DIR}" -P ${TAIXUENGINE_ROOT_DIR}/cmake/MoveByPath.cmake
    COMMAND ${CMAKE_COMMAND} -DSRC_PATH="${ENGINE_ROOT_DIR}/src/editor/res" -DDEST_PATH="${OUTPUT_DIR}" -P ${TAIXUENGINE_ROOT_DIR}/cmake/MoveByPath.cmake
)

if(${CMAKE_BUILD_TYPE})
    message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

    if(${CMAKE_BUILD_TYPE} NOT STREQUAL "Debug")
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory "${BINARY_ROOT_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy "${ENGINE_ROOT_DIR}/${TARGET_NAME}.json" "${BINARY_ROOT_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy "${OUTPUT_DIR}/${TARGET_NAME}" "${BINARY_ROOT_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy "${OUTPUT_DIR}/imgui.ini" "${BINARY_ROOT_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "res" "${BINARY_ROOT_DIR}/res"
            COMMAND ${CMAKE_COMMAND} -E remove_directory "${BINARY_ROOT_DIR}/${ENGINE_ASSET_DIR}"
            COMMAND ${CMAKE_COMMAND} -E copy_directory "${ENGINE_ROOT_DIR}/${ENGINE_ASSET_DIR}" "${BINARY_ROOT_DIR}/${ENGINE_ASSET_DIR}"
        )
    endif()
endif()
