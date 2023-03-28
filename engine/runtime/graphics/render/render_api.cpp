//
// Created by xmmmmmovo on 2023/3/28.
//

#include "render_api.hpp"

namespace taixu {

void openglAPILoader() {
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("Failed to initialize GLAD");
        exit(1);
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
}

void loadAPI(RenderAPI api) {
    switch (api) {
        case RenderAPI::OPENGL:
            openglAPILoader();
            break;
        case RenderAPI::NONE:
            break;
    }
}
}// namespace taixu