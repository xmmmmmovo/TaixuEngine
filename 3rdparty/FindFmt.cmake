# fmt
CPMAddPackage(
        NAME fmt
        GITHUB_REPOSITORY fmtlib/fmt
        GIT_TAG 10.1.1
        GIT_SHALLOW TRUE
)

if(fmt_ADDED)
        set_target_properties(fmt PROPERTIES CXX_STANDARD 20)
        set_target_properties(fmt-header-only PROPERTIES CXX_STANDARD 20)
endif()
