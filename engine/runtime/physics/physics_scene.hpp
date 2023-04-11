#ifndef TAIXUENGINE_PHYSICS_SCENE
#define TAIXUENGINE_PHYSICS_SCENE

#include "physics/Jolt_utilities.hpp"
#include <Jolt/Jolt.h>

#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>


#include "resource/ecs/entity_component/transform/transform_component.hpp"

namespace taixu
{
    struct JoltPhysics
    {
        std::unique_ptr<JPH::PhysicsSystem>            physics_system {nullptr};
        std::unique_ptr<JPH::JobSystem>                job_system {nullptr};
        std::unique_ptr<JPH::TempAllocator>            temp_allocator {nullptr};
        std::unique_ptr<JPH::BroadPhaseLayerInterface> broad_phase_layer_interface {nullptr};
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

class PhysicsScene
{
public:
    PhysicsScene() = default;
    JoltPhysics m_physics;
    JoltParameters m_parameter;
    void initialize();

    uint32_t createRigidBodyActor();
    void removeRigidBodyActor(uint32_t body_id);

    void tick();
    void updateGlobalTransform(TransformComponent* _transf);
};

}

#endif /* TAIXUENGINE_PHYSICS_SCENE */
