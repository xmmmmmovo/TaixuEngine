#include "perspective_camera.hpp"

namespace taixu {

glm::mat4 PerspectiveCamera::getViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() { return projection_matrix; }


}// namespace taixu