//
// Created by xmmmmmovo on 2023/5/14.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_MATRICES_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_MATRICES_HPP

#include <glm/glm.hpp>

namespace taixu {

struct Matrices {
    glm::mat4 projection;
    glm::mat4 view;
    glm::mat4 vp;
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_MATRICES_HPP
