cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# set vcpkg for cmake
if (NOT DEFINED ENV{VCPKG_ROOT})
    set(ENV{VCPKG_ROOT} ${PROJECT_SOURCE_DIR}/3rdparty/vcpkg)
endif()

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)        
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# for project properties
set(ENGINE_VERSION 0.01)

project(
        TaixuEngine
        VERSION ${ENGINE_VERSION}
        DESCRIPTION "An Game Engine."
        HOMEPAGE_URL "https://github.com/TaixuEngineGroup/TaixuEngine"
        LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(engine)