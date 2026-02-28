# Boost
CPMAddPackage(
    NAME Boost
    VERSION 1.85.0
    GITHUB_REPOSITORY "boostorg/boost"
    GIT_TAG "boost-1.85.0"
)

if(Boost_ADDED)
    # Set Boost as header-only by default, can be overridden by components
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)

    # Add commonly used components if needed
    # Add more components as required: filesystem system thread regex etc.

    # Set C++ standard for Boost
    set_target_properties(Boost::boost PROPERTIES CXX_STANDARD 23)
    set_target_properties(Boost::disable_autolinking PROPERTIES CXX_STANDARD 23)
    set_target_properties(Boost::dynamic_linking PROPERTIES CXX_STANDARD 23)

    # Create commonly used aliases
    if(TARGET Boost::boost)
        add_library(Boost::headers ALIAS Boost::boost)
    endif()
endif()
