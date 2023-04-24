#ifndef TAIXUENGINE_RIGID_BODY_COMPONENT
#define TAIXUENGINE_RIGID_BODY_COMPONENT

#include <Jolt/Jolt.h>

#include "resource/ecs/entity_component/entity_component.hpp"
#include "resource/ecs/entity_component/transform/transform_component.hpp"
#include "physics/physics_scene.hpp"


namespace taixu
{
    enum class RigidBodyShapeType
    {
        BOX,
        SPHERE,
        // capsule,
        INVALID
    };

    enum class MotionType
    {
        STATIC,
        DYNAMIC
    };

    struct RigidbodyInfo
    {
        RigidBodyShapeType stype;
        MotionType mtype;
        std::uint32_t GO;
        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;
        
    };
class PhysicsScene;
class RigidBodyComponent : public EntityComponent
{
public:
    RigidBodyComponent() = default;
    RigidBodyComponent(std::uint32_t go,
    TransformComponent *transform,
    std::weak_ptr<PhysicsScene> physics_scene)
    :GO(go),
    transform_component(std::move(transform)),
    current_scene(physics_scene){}

    std::uint32_t GO;
    JPH::BodyID body_id;
    RigidBodyShapeType type {RigidBodyShapeType::INVALID};

    std::weak_ptr<PhysicsScene> current_scene;
    TransformComponent *transform_component;
    

    void initialize(RigidBodyShapeType stype, MotionType mtype);
    std::uint32_t getGO(){return GO;};
    void tick();

};

}

#endif /* TAIXUENGINE_RIGID_BODY_COMPONENT */
