# Glfw3
CPMAddPackage(
        NAME glfw3
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.4
        OPTIONS
            "GLFW_BUILD_TESTS Off"
            "GLFW_BUILD_EXAMPLES Off"
            "GLFW_BUILD_DOCS Off"
            "GLFW_INSTALL Off"
            "GLFW_USE_HYBRID_HPG On"
)
