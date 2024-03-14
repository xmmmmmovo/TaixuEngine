# assimp
CPMAddPackage(
        NAME assimp
        GITHUB_REPOSITORY assimp/assimp
        GIT_TAG 5d5496f1ad895297cede723b3c96b513263f82ed
        OPTIONS
        "ASSIMP_WARNINGS_AS_ERRORS OFF"
        "ASSIMP_BUILD_TESTS Off"
        "ASSIMP_BUILD_EXAMPLES Off"
        "ASSIMP_BUILD_DOCS Off"
        "ASSIMP_INSTALL_PDB Off"
)