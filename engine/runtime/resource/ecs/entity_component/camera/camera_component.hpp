#ifndef TAIXUENGINE_CAMERA_COMPONENT
#define TAIXUENGINE_CAMERA_COMPONENT

#include "resource/ecs/entity_component/entity_component.hpp"
#include "graphics/render/perspective_camera.hpp"
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
