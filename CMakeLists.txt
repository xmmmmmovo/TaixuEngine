cmake_minimum_required(VERSION 3.20)

# default for cxx23 feature
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)
# This line used for cross platform compilation
set(CMAKE_CXX_EXTENSIONS OFF)

# compile config
option(USE_CCACHE "ccache accelerate the compile" OFF)
option(USE_VCPKG "vcpkg manager" OFF)
option(USE_PCH "pre compile" ON)
option(WARNINGS "warnings" ON)

option(USE_VULKAN "use vulkan" ON)
option(USE_WGPU "use webgpu" ON)
option(USE_HLSL "use hlsl" OFF)

option(USE_NOEXCEPT "use noexcept" ON)

# for project properties
set(TX_ENGINE_NAME "TaixuEngine")
set(TX_ENGINE_VERSION 0.1.1)

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

if(MSVC)
    set(TAIXU_WARNINGS_DEF "/W4 /WX /permissive- /RTCc")
else()
    set(TAIXU_WARNINGS_DEF
        "-Wall -Wextra -Weffc++ -Werror=uninitialized -Werror=return-type -Wconversion -Wsign-compare -Werror=unused-result
                        -Werror=suggest-override -Wzero-as-null-pointer-constant -Wmissing-declarations -Wold-style-cast -Wnon-virtual-dtor"
    )
endif()

project(
    ${TX_ENGINE_NAME}
    VERSION ${TX_ENGINE_VERSION}
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

# setup hooks
include(FindHooks)

add_subdirectory(engine)
add_subdirectory(docs)
add_subdirectory(tests)
