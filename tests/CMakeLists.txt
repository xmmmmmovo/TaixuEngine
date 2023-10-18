cmake_minimum_required(VERSION 3.20)

project(TaixuEngineTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/FindTools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

include(../3rdparty/FindCatch2.cmake)

# ---- Add Options ----

if (APPLE)
    # TODO: Delete this line after assimp group fix this issue: #4864 #3933
    # Just for my mac
    link_directories(/opt/homebrew/Cellar/minizip/1.2.13/lib)
endif (APPLE)

# ---- Add Tests ----

file(GLOB_RECURSE tests_lib "lib/*.hpp")

file(GLOB_RECURSE unit_tests_src "unit_tests/*.cpp")
file(GLOB_RECURSE benchmarks_src "benchmarks/*.cpp")

set(TARGET_NAME taixu_tests)
set(TEST_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Add a testing executable
add_executable(${TARGET_NAME} ${unit_tests_src} ${benchmarks_src})

target_link_libraries(${TARGET_NAME} TaixuRuntime Catch2::Catch2WithMain)

enable_testing()
add_test(${TARGET_NAME} taixu_unit_tests)

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -DSRC_PATH="${TEST_ROOT_DIR}/test-assets" -DDEST_PATH="${OUTPUT_DIR}/test-assets" -P ${TAIXUENGINE_ROOT_DIR}/cmake/MoveByPath.cmake
)
