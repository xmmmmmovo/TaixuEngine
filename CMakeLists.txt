cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# compile config
option(USE_CCACHE "ccache accelerate the compile" OFF)
option(USE_VCPKG "vcpkg manager" OFF)
option(USE_PCH "pre compile" ON)
option(WARNINGS "warnings" OFF)

option(USE_VULKAN "use vulkan" ON)
option(USE_HLSL "use hlsl" ON)

# for project properties
set(ENGINE_VERSION 0.1.1)

# add dirs to module path to make include more convenient
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)

if(USE_VCPKG)
    # set vcpkg for cmake
    if(NOT DEFINED ENV{VCPKG_ROOT})
        set(ENV{VCPKG_ROOT} "./3rdparty/vcpkg")
    endif()

    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

set(TAIXU_WARNINGS_DEF "-Wall -Wextra -Weffc++ -Werror=uninitialized -Werror=return-type -Wconversion -Wsign-compare -Werror=unused-result 
                        -Werror=suggest-override -Wzero-as-null-pointer-constant -Wmissing-declarations -Wold-style-cast -Wnon-virtual-dtor")

project(
    TaixuEngine
    VERSION ${ENGINE_VERSION}
    DESCRIPTION "A Game Engine."
    HOMEPAGE_URL "https://github.com/TaixuEngineGroup/TaixuEngine"
    LANGUAGES CXX C
)

set(TAIXUENGINE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${TAIXUENGINE_ROOT_DIR}/bin")
set(BINARY_ROOT_DIR "${CMAKE_INSTALL_PREFIX}/")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if("${CMAKE_RUNTIME_OUTPUT_DIRECTORY}" STREQUAL "")
    set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
else()
    set(OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()

# add cmake package manager
set(CPM_SOURCE_CACHE "${TAIXUENGINE_ROOT_DIR}/.cpm_cache")
include(CPM)

add_subdirectory(engine)
add_subdirectory(docs)
add_subdirectory(tests)