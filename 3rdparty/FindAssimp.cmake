if (APPLE)
    # TODO: Delete this line after assimp group fix this issue: #4864 #3933
    # Just for my mac
    link_directories(/opt/homebrew/Cellar/minizip/1.2.13/lib)
endif (APPLE)

# assimp
CPMAddPackage(
        NAME assimp
        GITHUB_REPOSITORY assimp/assimp
        GIT_TAG v5.2.5
        GIT_SHALLOW TRUE
        OPTIONS
        "ASSIMP_WARNINGS_AS_ERRORS OFF"
        "ASSIMP_BUILD_TESTS Off"
        "ASSIMP_BUILD_EXAMPLES Off"
        "ASSIMP_BUILD_DOCS Off"
        "ASSIMP_INSTALL_PDB Off"
)