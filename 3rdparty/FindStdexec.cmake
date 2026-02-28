# stdexec - Standard Executors for C++
CPMAddPackage(
    NAME stdexec
    GITHUB_REPOSITORY "NVIDIA/stdexec"
    GIT_TAG "main" # Using main branch as this is still in development
    OPTIONS
    "STDEXEC_BUILD_TESTING Off"
    "STDEXEC_BUILD_EXAMPLES Off"
    "STDEXEC_BUILD_DOCS Off"
    "STDEXEC_BUILD_BENCHMARKS Off"
)

if(stdexec_ADDED)
    # Set C++23 standard for stdexec (requires latest C++ standards)
    set_target_properties(stdexec PROPERTIES CXX_STANDARD 23)

    # stdexec might need additional compiler flags for concepts and coroutines
    if(MSVC)
        target_compile_options(stdexec PRIVATE
            /std:c++latest
            /permissive-
            /await:strict
        )
    else()
        target_compile_options(stdexec PRIVATE
            -std=c++23
            -fcoroutines
            -fconcepts
        )
    endif()

    # Create convenient alias
    add_library(Stdexec::Stdexec ALIAS stdexec)

    # If header-only target exists, also set its properties
    if(TARGET stdexec::header_only)
        set_target_properties(stdexec::header_only PROPERTIES CXX_STANDARD 23)
        add_library(Stdexec::Header ALIAS stdexec::header_only)
    endif()
endif()
