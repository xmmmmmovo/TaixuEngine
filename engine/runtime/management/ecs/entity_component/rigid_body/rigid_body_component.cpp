#include "rigid_body_component.hpp"

namespace taixu {
void RigidBodyComponent::init(RigidBodyShapeType stype,
                                    MotionType         mtype) {
    RigidbodyInfo rgdInfo;
    rgdInfo.GO       = _GO;
    rgdInfo.stype    = stype;
    rgdInfo.mtype    = mtype;
    rgdInfo.position = transform_component->position;
    rgdInfo.rotation = glm::vec3(transform_component->rotation.x,
                                 transform_component->rotation.y,
                                 transform_component->rotation.z);
    rgdInfo.scale    = transform_component->scale;
    body_id          = current_scene.lock()->createRigidBodyActor(rgdInfo);
}

void RigidBodyComponent::tick() {
    current_scene.lock()->updateGlobalTransform(transform_component, body_id);
}
}// namespace taixu
