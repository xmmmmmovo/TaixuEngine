//
// Created by xmmmmmovo on 2023/5/17.
//

#ifndef ENGINE_RUNTIME_GAMEPLAY_PLAYER_CAMERA_CAMERA_HPP
#define ENGINE_RUNTIME_GAMEPLAY_PLAYER_CAMERA_CAMERA_HPP

#include <glm/glm.hpp>

#include <common/base/macro.hpp>

namespace taixu {
class Camera {
    PROTOTYPE_ONLY_GETTER(protected, glm::mat4, view_matrix);
    PROTOTYPE_ONLY_GETTER(protected, glm::mat4, projection_matrix);

    void rorateX(float angle) {}

    void rorateY(float angle) {}

    void rorateZ(float angle) {}

    void move(glm::vec3 const& direction) {}
};
}// namespace taixu

#endif// ENGINE_RUNTIME_GAMEPLAY_PLAYER_CAMERA_CAMERA_HPP
