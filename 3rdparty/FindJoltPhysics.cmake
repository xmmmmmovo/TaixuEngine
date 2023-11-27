CPMAddPackage(
        NAME JoltPhysics
        GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
        GIT_TAG "194698f37ea849bd200533746a82a7b6acf32c4e"
        GIT_SHALLOW TRUE
        SOURCE_SUBDIR "Build"
)

set_target_properties(Jolt PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")