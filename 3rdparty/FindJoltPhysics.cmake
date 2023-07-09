CPMAddPackage(
        NAME JoltPhysics
        GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
        GIT_TAG "b6c184a25d8f32527c0a217ac5c512f61f26f21a"
        GIT_SHALLOW TRUE
        SOURCE_SUBDIR "Build"
)

set_target_properties(Jolt PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")