#ifndef TAIXUENGINE_PHYSICS_SCENE
#define TAIXUENGINE_PHYSICS_SCENE


#include "Jolt/Jolt.h"

#include "Jolt/Core/Factory.h"
#include "Jolt/Core/JobSystemThreadPool.h"
#include "Jolt/Core/TempAllocator.h"
#include "Jolt/Physics/Body/BodyActivationListener.h"
#include "Jolt/Physics/Body/BodyCreationSettings.h"
#include "Jolt/Physics/Collision/Shape/BoxShape.h"
#include "Jolt/Physics/Collision/Shape/SphereShape.h"
#include "Jolt/Physics/PhysicsSettings.h"
#include "Jolt/Physics/PhysicsSystem.h"
#include "Jolt/RegisterTypes.h"

#include "Jolt_utilities.hpp"
#include "management/ecs/entity_component/rigid_body/rigid_body_component.hpp"
#include "management/ecs/entity_component/transform/transform_component.hpp"

namespace taixu
{
    struct JoltPhysics
    {
        std::unique_ptr<JPH::PhysicsSystem>            physics_system {nullptr};
        std::unique_ptr<JPH::JobSystem>                job_system {nullptr};
        std::unique_ptr<JPH::TempAllocator>            temp_allocator {nullptr};
        std::unique_ptr<JPH::BroadPhaseLayerInterface> broad_phase_layer_interface {nullptr};
        std::unique_ptr<ObjectVsBroadPhaseLayerFilterImpl>      object_vs_broadphase_layer_filter{nullptr};
        std::unique_ptr<ObjectLayerPairFilterImpl>             object_vs_object_layer_filter{nullptr};
        std::unique_ptr<MyBodyActivationListener>      body_activation_listener{nullptr};
        std::unique_ptr<MyContactListener>             contact_listener{nullptr};
        // JPH::PhysicsSystem*            physics_system {nullptr};
        // JPH::JobSystem*                job_system {nullptr};
        // JPH::TempAllocator*            temp_allocator {nullptr};
        // JPH::BroadPhaseLayerInterface* broad_phase_layer_interface {nullptr};
        // MyBodyActivationListener*      body_activation_listener{nullptr};
        // MyContactListener*             contact_listener{nullptr};
        int m_collision_steps {1};
        int m_integration_substeps {1};
    };

    struct JoltParameters
    {
        // scene setting
        uint32_t m_max_body_count {10240};
        uint32_t m_body_mutex_count {0} ;
        uint32_t m_max_body_pairs {65536};
        uint32_t m_max_contact_constraints {10240};

        // job setting
        uint32_t m_max_job_count {1024};
        uint32_t m_max_barrier_count {8};
        uint32_t m_max_concurrent_job_count {4};

        glm::vec3 m_gravity {0.f, 0.f, -9.8f}; 
    };

    // struct PhysicsGOmap
    // {
    //     std::uint32_t GO;
    //     JPH::BodyID shape_id;
    // };   

    struct RigidbodyInfo;
    enum class RigidBodyShapeType;

class PhysicsScene
{
public:
    PhysicsScene() = default;
    JoltPhysics m_physics;
    JoltParameters m_parameter;
    ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
    ObjectLayerPairFilterImpl object_vs_object_layer_filter;
    JPH::BodyID sphere_id;
    int step =0;
    
    std::vector<RigidbodyInfo> dirty_rgd;
    std::vector<JPH::BodyID> current_bodies;

    void initialize();
    JPH::Shape* toShape(RigidBodyShapeType shape, const glm::vec3& scale);
    JPH::BodyID createRigidBodyActor(RigidbodyInfo rgdInfo);
    void createRigidBodyActor();
    void removeRigidBodyActor(JPH::BodyID body_id);

    void tick();
    void updateGlobalTransform(TransformComponent* _transf, JPH::BodyID body_id);
};

}

#endif /* TAIXUENGINE_PHYSICS_SCENE */
