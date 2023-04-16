CPMAddPackage(
    NAME JoltPhysics
    GIT_REPOSITORY "https://github.com/jrouwe/JoltPhysics"
    GIT_TAG "364071164528f173539d49c7043e94798a40473d"
    #GIT_TAG "a441f371e8367fa2731ce1a55d20047f6826b961"
    #VERSION 2.0.1
    SOURCE_SUBDIR "Build"
)

set_target_properties(Jolt PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")