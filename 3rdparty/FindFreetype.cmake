CPMAddPackage(
        NAME freetype
        GIT_REPOSITORY https://github.com/aseprite/freetype2.git
        GIT_TAG e8ebfe988b5f57bfb9a3ecb13c70d9791bce9ecf
        GIT_SHALLOW TRUE
)

if (freetype_ADDED)
    add_library(Freetype::Freetype ALIAS freetype)
endif ()