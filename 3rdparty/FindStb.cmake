# stb
CPMAddPackage(
        NAME stb
        GIT_REPOSITORY https://github.com/nothings/stb.git
        GIT_TAG ae721c50eaf761660b4f90cc590453cdb0c2acd0
        DOWNLOAD_ONLY YES
)

if(stb_ADDED)
        FILE(GLOB stb_headers CONFIGURE_DEPENDS
                ${stb_SOURCE_DIR}/*.h)
        add_library(stb INTERFACE ${stb_sources})
        set_target_properties(stb PROPERTIES CXX_STANDARD 23)
        target_include_directories(stb
                INTERFACE
                $<BUILD_INTERFACE:${stb_SOURCE_DIR}>
        )
endif()
