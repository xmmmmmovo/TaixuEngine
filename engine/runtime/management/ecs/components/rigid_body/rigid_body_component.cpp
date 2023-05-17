#include "rigid_body_component.hpp"

namespace taixu {

void RigidBodyComponent::init(RigidBodyShapeType stype,
                                    MotionType         mtype,
                                    glm::vec3 position,
                                    glm::vec3 scl,
                                    Entity entt,
                                    std::weak_ptr<PhysicsScene> _physics_scene
                            ) 
{
    RigidbodyInfo rgdInfo;
    rgdInfo.stype    = stype;
    rgdInfo.mtype    = mtype;
    rgdInfo.position = position;
    rgdInfo.scale    = scl;
    body_id          = _physics_scene.lock()->createRigidBodyActor(rgdInfo);
}


}// namespace taixu
