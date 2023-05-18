#ifndef TAIXUENGINE_CAMERA_COMPONENT
#define TAIXUENGINE_CAMERA_COMPONENT

#include "gameplay/player/camera/perspective_camera.hpp"

namespace taixu {
class CameraComponent {
public:
    CameraComponent() = default;

    std::unique_ptr<PerspectiveCamera> character_camera{
            std::make_unique<PerspectiveCamera>()};
};


}// namespace taixu

#endif /* TAIXUENGINE_CAMERA_COMPONENT */
