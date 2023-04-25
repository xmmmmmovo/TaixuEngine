#include "rigid_body_component.hpp"

namespace taixu
{
    void RigidBodyComponent::initialize(RigidBodyShapeType stype, MotionType mtype) {
        RigidbodyInfo rgdInfo;
        rgdInfo.GO = GO;
        rgdInfo.stype = stype;
        rgdInfo.mtype = mtype;
        rgdInfo.position = transform_component->position;
        rgdInfo.rotation = transform_component->rotation_degrees;
        rgdInfo.scale = transform_component->scale;
        body_id = current_scene.lock()->createRigidBodyActor(rgdInfo);
    }

    void RigidBodyComponent::tick() {
        current_scene.lock()->updateGlobalTransform(transform_component,body_id);
    }
}

