//
// Created by xmmmmmovo on 2023/4/23.
//
#include "render_api.hpp"

namespace taixu {

/**
 * @brief OpenGL API加载器
 */
class OGLAPILoader : public AbstractGraphicsAPILoader {
public:
    void initLoad() const override {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    void apiLoad(GLFWwindow *window) override {
        glfwMakeContextCurrent(window);

        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if (!gladLoadGLLoader(
                    reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            spdlog::error("Failed to initialize GLAD");
            exit(1);
        }

        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);
        spdlog::info("Cull face enabled");
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        _window = window;
    }

    void swapBuffers() const override { glfwSwapBuffers(_window); }
};

std::unique_ptr<AbstractGraphicsAPILoader>
createGraphicsAPILoader(GraphicsAPI api) {
    switch (api) {
        case GraphicsAPI::OPENGL:
            return std::make_unique<OGLAPILoader>();
        default:
            spdlog::error("Invalid graphics API choice");
            exit(1);
    }
}

}// namespace taixu