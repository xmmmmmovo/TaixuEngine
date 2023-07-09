#catch2
CPMAddPackage(
        NAME catch2
        GITHUB_REPOSITORY catchorg/Catch2
        VERSION 3.2.1
        GIT_SHALLOW TRUE
        OPTIONS
        "CATCH_INSTALL_DOCS OFF"
)