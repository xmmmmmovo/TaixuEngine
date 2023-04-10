CPMAddPackage(
    NAME JoltPhysics
    GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
    VERSION 2.0.1
    SOURCE_SUBDIR "Build"
)

set_target_properties(Jolt PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")