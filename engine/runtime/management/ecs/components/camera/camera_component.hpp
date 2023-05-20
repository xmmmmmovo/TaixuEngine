#ifndef TAIXUENGINE_CAMERA_COMPONENT
#define TAIXUENGINE_CAMERA_COMPONENT

#include "gameplay/player/camera/euler_camera.hpp"

namespace taixu {
class CameraComponent {
public:
    CameraComponent() = default;

    std::unique_ptr<EulerCamera> character_camera{
            std::make_unique<EulerCamera>()};
};


}// namespace taixu

#endif /* TAIXUENGINE_CAMERA_COMPONENT */
