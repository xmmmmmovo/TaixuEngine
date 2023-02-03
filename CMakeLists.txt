cmake_minimum_required(VERSION 3.20)

set(ENGINE_VERSION 0.01)

project(
        TaixuEngine
        VERSION ${ENGINE_VERSION}
        DESCRIPTION "An Game Engine."
        HOMEPAGE_URL "https://github.com/TaixuEngineGroup/TaixuEngine"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(engine)