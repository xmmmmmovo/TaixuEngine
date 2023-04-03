#ifndef TAIXUENGINE_CAMERA_COMPONENT
#define TAIXUENGINE_CAMERA_COMPONENT

#include "resource/ecs/entity_component.hpp"
#include "graphics/render/perspective_camera.hpp"
namespace taixu
{
class CameraComponent:
{
public:
    PerspectiveCamera *character_camera{nullptr};

};



}

#endif /* TAIXUENGINE_CAMERA_COMPONENT */
