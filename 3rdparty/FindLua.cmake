CPMAddPackage(
    NAME lua
    GIT_REPOSITORY lua/lua
    VERSION 5.3.5
    DOWNLOAD_ONLY YES
)

if (lua_ADDED)
    # lua has no CMake support, so we create our own target
    FILE(GLOB lua_sources ${lua_SOURCE_DIR}/*.c)
    list(REMOVE_ITEM lua_sources "${lua_SOURCE_DIR}/lua.c" "${lua_SOURCE_DIR}/luac.c")
    add_library(lua STATIC ${lua_sources})

    target_include_directories(lua
        PUBLIC
        $<BUILD_INTERFACE:${lua_SOURCE_DIR}>
    )
endif()