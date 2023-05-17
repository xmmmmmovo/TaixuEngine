#include "rigid_body_component.hpp"

namespace taixu {

void RigidBodyComponent::init(RigidBodyShapeType stype,
                                    MotionType         mtype
                                    /*TransformComponent         *transform_component*/) {
    RigidbodyInfo rgdInfo;
    rgdInfo.stype    = stype;
    rgdInfo.mtype    = mtype;
    rgdInfo.position = transform_component->_position;
    rgdInfo.rotation = glm::vec3(transform_component->_rotation.x,
                                 transform_component->_rotation.y,
                                 transform_component->_rotation.z);
    rgdInfo.scale    = shapeScale;
    body_id          = current_scene.lock()->createRigidBodyActor(rgdInfo);
}

void RigidBodyComponent::tick() {
    current_scene.lock()->updateGlobalTransform(transform_component, body_id);
}

}// namespace taixu
