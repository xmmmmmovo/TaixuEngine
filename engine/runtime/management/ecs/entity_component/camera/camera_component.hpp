#ifndef TAIXUENGINE_CAMERA_COMPONENT
#define TAIXUENGINE_CAMERA_COMPONENT

#include "gameplay/player/perspective_camera.hpp"

namespace taixu {
class CameraComponent {
public:
    CameraComponent() = default;

    std::unique_ptr<PerspectiveCamera> character_camera{nullptr};
    void                               init();
    void                               setCameraPosition(glm::vec3 position);
    void                               setCameraLookAt();
};


}// namespace taixu

#endif /* TAIXUENGINE_CAMERA_COMPONENT */
