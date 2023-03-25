cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# compile config
option(USE_CCACHE "ccache accelerate the compile" OFF)
option(USE_VCPKG "vcpkg manager" OFF)
option(USE_PCH "pre compile" ON)
option(WARNINGS "warnings" OFF)

# for project properties
set(ENGINE_VERSION 0.01)

if (USE_VCPKG)
    # set vcpkg for cmake
    if (NOT DEFINED ENV{VCPKG_ROOT})
        set(ENV{VCPKG_ROOT} "./3rdparty/vcpkg")
    endif ()

    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif ()

if (WARNINGS)
    add_definitions(-Wall)
endif ()

project(
        TaixuEngine
        VERSION ${ENGINE_VERSION}
        DESCRIPTION "A Game Engine."
        HOMEPAGE_URL "https://github.com/TaixuEngineGroup/TaixuEngine"
        LANGUAGES CXX C
)

# add cmake package manager
include(cmake/CPM.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(TAIXUENGINE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${TAIXUENGINE_ROOT_DIR}/bin")
set(BINARY_ROOT_DIR "${CMAKE_INSTALL_PREFIX}/")

configure_file(cmake/path.hpp.in ${TAIXUENGINE_ROOT_DIR}/engine/runtime/core/base/path.hpp @ONLY)

add_subdirectory(engine)
add_subdirectory(docs)
add_subdirectory(tests)