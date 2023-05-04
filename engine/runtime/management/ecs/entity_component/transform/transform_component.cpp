#include "transform_component.hpp"
namespace taixu {
void TransformComponent::tick() {}

void TransformComponent::setPosition(glm::vec3 pos) { position = pos; }

void TransformComponent::setScale(glm::vec3 scl) { scale = scl; }

void TransformComponent::setRotation(glm::quat rotate) { rotate = rotate; }

}// namespace taixu