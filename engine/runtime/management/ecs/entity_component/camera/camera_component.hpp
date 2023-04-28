#ifndef TAIXUENGINE_CAMERA_COMPONENT
#define TAIXUENGINE_CAMERA_COMPONENT

#include "gameplay/player/perspective_camera.hpp"
#include "management/ecs/entity_component/entity_component.hpp"
namespace taixu
{
class CameraComponent
{
public:
    CameraComponent()=default;
    
    std::unique_ptr<PerspectiveCamera> character_camera{nullptr};
    void initialize();
    void setCameraPosition(glm::vec3 position);
    void setCameraLookAt();

};



}

#endif /* TAIXUENGINE_CAMERA_COMPONENT */
