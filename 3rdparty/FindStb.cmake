# stb
CPMAddPackage(
        NAME stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG f4a71b13373436a2866c5d68f8f80ac6f0bc1ffe
        GIT_SHALLOW TRUE
        DOWNLOAD_ONLY YES
)

if (stb_ADDED)
    FILE(GLOB stb_headers CONFIGURE_DEPENDS
            ${stb_SOURCE_DIR}/*.h)
    add_library(stb INTERFACE ${stb_sources})
    target_include_directories(stb
            INTERFACE
            $<BUILD_INTERFACE:${stb_SOURCE_DIR}>
            )
endif ()
