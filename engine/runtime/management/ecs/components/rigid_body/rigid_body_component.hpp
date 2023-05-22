#ifndef TAIXUENGINE_RIGID_BODY_COMPONENT
#define TAIXUENGINE_RIGID_BODY_COMPONENT

#include "Jolt/Jolt.h"

#include "management/ecs/components/transform/transform_component.hpp"
#include "management/ecs/core/ecs_types.hpp"
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
    RigidBodyComponent(std::weak_ptr<PhysicsScene> physics_scene)
        : current_scene(physics_scene) {}

    JPH::BodyID        body_id;
    Entity             entity;
    RigidBodyShapeType type{RigidBodyShapeType::INVALID};

    std::weak_ptr<PhysicsScene> current_scene;

    void init(RigidBodyShapeType stype, MotionType mtype, glm::vec3 pos,
              glm::vec3 scl, Entity entt,
              std::weak_ptr<PhysicsScene> _physics_scene);
};

}// namespace taixu

#endif /* TAIXUENGINE_RIGID_BODY_COMPONENT */
