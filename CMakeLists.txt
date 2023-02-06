cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# compile config
set(USE_CCACHE OFF)
set(USE_VCPKG OFF)

# for project properties
set(ENGINE_VERSION 0.01)

if(USE_VCPKG)
    # set vcpkg for cmake
    if (NOT DEFINED ENV{VCPKG_ROOT})
        set(ENV{VCPKG_ROOT} "./3rdparty/vcpkg")
    endif ()

    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(
        TaixuEngine
        VERSION ${ENGINE_VERSION}
        DESCRIPTION "A Game Engine."
        HOMEPAGE_URL "https://github.com/TaixuEngineGroup/TaixuEngine"
        LANGUAGES CXX C
)

# add cmake package manager
include(cmake/CPM.cmake)

add_subdirectory(engine)