#include "camera_component.hpp"

void taixu::CameraComponent::initialize() {
    character_camera=std::make_unique<PerspectiveCamera>();
    
}

void taixu::CameraComponent::setCameraPosition(glm::vec3 position) {
    character_camera->Position=position;
    character_camera->updateCameraVectors();
}

void taixu::CameraComponent::setCameraLookAt() {

}
