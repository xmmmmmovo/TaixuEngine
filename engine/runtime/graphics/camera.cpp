/**/#include "camera.hpp"

namespace taixu::cg {
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(Position, Position + Front, Up);
    }
}// namespace taixu::cg