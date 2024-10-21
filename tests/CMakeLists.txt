cmake_minimum_required(VERSION 3.20)

# ---- Options ----
option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----
include(FindTools)

# ---- Dependencies ----
include(FindCatch2)

# ---- Add Tests ----
file(GLOB_RECURSE unit_tests_src "unit_tests/*.cpp")
file(GLOB_RECURSE benchmarks_src "benchmarks/*.cpp")

set(ALL_FILE ${unit_tests_src} ${benchmarks_src})

set(TARGET_NAME_ALL TaixuAllTests)
set(TEST_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Add a testing executable
add_executable(${TARGET_NAME_ALL} ${unit_tests_src} ${benchmarks_src})

# ---- Add Options ----
set_target_properties(${TARGET_NAME_ALL} PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED True)

if(MSVC)
    target_compile_options(${TARGET_NAME_ALL} PRIVATE "/utf-8" "/MP")
    target_compile_definitions(${TARGET_NAME_ALL} PRIVATE UNICODE _UNICODE)
endif()

# ---- Link Libraries ----
target_link_libraries(${TARGET_NAME_ALL} Catch2::Catch2WithMain)
target_link_libraries(${TARGET_NAME_ALL} TaixuRuntime)
target_include_directories(${TARGET_NAME_ALL} PRIVATE $<TARGET_PROPERTY:TaixuRuntime,INCLUDE_DIRECTORIES>)

enable_testing()
add_test(${TARGET_NAME_ALL} taixu_tests)

add_custom_command(TARGET ${TARGET_NAME_ALL} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -DSRC_PATH="${TEST_ROOT_DIR}/test-assets" -DDEST_PATH="${OUTPUT_DIR}" -P ${TAIXUENGINE_ROOT_DIR}/cmake/MoveByPath.cmake
)
