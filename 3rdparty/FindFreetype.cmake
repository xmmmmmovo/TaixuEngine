CPMAddPackage(
        NAME freetype
        URL https://download.savannah.gnu.org/releases/freetype/freetype-2.14.1.tar.gz
)

if (freetype_ADDED)
    add_library(Freetype::Freetype ALIAS freetype)
endif ()
