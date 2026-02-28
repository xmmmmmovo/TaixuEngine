# EnTT - Gaming RTTI made simple
CPMAddPackage(
    NAME entt
    GITHUB_REPOSITORY "skypjack/entt"
    VERSION 3.13.2
    OPTIONS
        "ENTT_BUILD_TESTING Off"
        "ENTT_BUILD_EXAMPLES Off"
        "ENTT_BUILD_BENCHMARKS Off"
        "ENTT_BUILD_DOCS Off"
        "ENTT_BUILD_INSTALL Off"
        "ENTT_BUILD_STATIC On"
)

if(entt_ADDED)
    # Set C++23 standard for EnTT to match project requirements
    set_target_properties(entt PROPERTIES CXX_STANDARD 23)

    # Create convenient alias for EnTT
    add_library(EnTT::EnTT ALIAS entt)

    # If header-only target exists, also set its properties
    if(TARGET entt::header)
        set_target_properties(entt::header PROPERTIES CXX_STANDARD 23)
        add_library(EnTT::Header ALIAS entt::header)
    endif()
endif()
