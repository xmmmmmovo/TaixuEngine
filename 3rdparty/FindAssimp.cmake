# assimp 
CPMAddPackage(
        NAME assimp
        GITHUB_REPOSITORY assimp/assimp
        GIT_TAG 35e4f1bf6492e11485336c1518485413c599e00e
        OPTIONS
        "ASSIMP_WARNINGS_AS_ERRORS Off"
        "ASSIMP_BUILD_TESTS Off"
        "ASSIMP_BUILD_EXAMPLES Off"
        "ASSIMP_BUILD_DOCS Off"
        "ASSIMP_BUILD_ZLIB On"
)