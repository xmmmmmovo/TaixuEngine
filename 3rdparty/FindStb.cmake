# stb
CPMAddPackage(
    NAME stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG 5736b15f7ea0ffb08dd38af21067c314d6a3aae9
)

if(stb_ADDED)
    FILE(GLOB stb_sources CONFIGURE_DEPENDS ${stb_SOURCE_DIR}/*.h)
    add_library(stb INTERFACE ${stb_sources})
    target_include_directories(stb
        INTERFACE
        $<BUILD_INTERFACE:${stb_SOURCE_DIR}>
    )
endif()
