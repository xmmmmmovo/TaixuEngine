#ifndef TAIXUENGINE_RIGID_BODY_COMPONENT
#define TAIXUENGINE_RIGID_BODY_COMPONENT

#include "Jolt/Jolt.h"

#include "management/ecs/components/transform/transform_component.hpp"
#include "management/physics/physics_scene.hpp"


namespace taixu {
enum class RigidBodyShapeType {
    BOX,
    SPHERE,
    // capsule,
    INVALID
};

enum class MotionType { STATIC, DYNAMIC };

struct RigidbodyInfo {
    RigidBodyShapeType stype;
    MotionType         mtype;
    std::uint32_t      GO;
    glm::vec3          position;
    glm::vec3          scale;
    glm::vec3          rotation;
};
class PhysicsScene;

class RigidBodyComponent {
public:
    RigidBodyComponent() = default;
    RigidBodyComponent(TransformComponent *trans,
                       std::weak_ptr<PhysicsScene> physics_scene)
        : transform_component(trans),current_scene(physics_scene) {}

    JPH::BodyID        body_id;
    RigidBodyShapeType type{RigidBodyShapeType::INVALID};
    glm::vec3 shapeScale;

    std::weak_ptr<PhysicsScene> current_scene;
    TransformComponent         *transform_component;
    
    void init(RigidBodyShapeType stype, MotionType mtype/*,TransformComponent *transform_component*/);
    void tick();
};

}// namespace taixu

#endif /* TAIXUENGINE_RIGID_BODY_COMPONENT */
