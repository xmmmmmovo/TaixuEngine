cmake_minimum_required(VERSION 3.20)

project(TaixuEngineTools LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# ---- Options ----

# ---- Dependencies ----

file(GLOB_RECURSE model_converter_source CONFIGURE_DEPENDS
        "model_converter/*.cpp" "model_converter/*.hpp")

add_executable(ModelConverterTool ${model_converter_source})

target_link_libraries(ModelConverterTool PRIVATE TaixuRuntime)