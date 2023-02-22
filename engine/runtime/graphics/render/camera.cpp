#include "camera.hpp"

namespace taixu {

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::getProjectionMatrix() { return ProjectionMatrix; }


}// namespace taixu