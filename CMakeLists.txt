cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# set vcpkg for cmake
if (NOT DEFINED ENV{VCPKG_ROOT})
    set(ENV{VCPKG_ROOT} "./3rdparty/vcpkg")
endif ()

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# for project properties
set(ENGINE_VERSION 0.01)

project(
        TaixuEngine
        VERSION ${ENGINE_VERSION}
        DESCRIPTION "An Game Engine."
        HOMEPAGE_URL "https://github.com/TaixuEngineGroup/TaixuEngine"
        LANGUAGES CXX C
)

# add cmake file
include(cmake/CPM.cmake)

# compile config
set(USE_CCACHE OFF)

add_subdirectory(engine)