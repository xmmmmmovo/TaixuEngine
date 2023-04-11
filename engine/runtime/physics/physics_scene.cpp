#include "physics_scene.hpp"

namespace taixu
{

void PhysicsScene::initialize() {
    JPH::Factory::sInstance = new JPH::Factory();
    JPH::RegisterTypes();
    m_physics.physics_system = std::make_unique<JPH::PhysicsSystem>();

    m_physics.job_system = std::make_unique<JPH::JobSystemThreadPool>(
        m_parameter.m_max_job_count,
        m_parameter.m_max_barrier_count,
        static_cast<int>(m_parameter.m_max_concurrent_job_count)
    );

    m_physics.temp_allocator = std::make_unique<JPH::TempAllocatorImpl>(10 * 1024 * 1024);
    m_physics.broad_phase_layer_interface = std::make_unique<BPLayerInterfaceImpl>();

    
    m_physics.physics_system->Init(m_parameter.m_max_body_count,
                                              m_parameter.m_body_mutex_count,
                                              m_parameter.m_max_body_pairs,
                                              m_parameter.m_max_contact_constraints,
                                              *(m_physics.broad_phase_layer_interface),
                                              ObjectvsBroadPhaseCanCollide,
                                              ObjectvsObjectCollide
                                            );

    // use the default setting
    m_physics.physics_system->SetPhysicsSettings(JPH::PhysicsSettings());

    m_physics.physics_system->SetGravity(JPH::Vec3(0.f,0.f,-9.8f));
    
}

uint32_t PhysicsScene::createRigidBodyActor(){
    // The main way to interact with the bodies in the physics system is through the body interface. There is a locking and a non-locking
	// variant of this. We're going to use the locking version (even though we're not planning to access bodies from multiple threads)
	JPH::BodyInterface &body_interface = m_physics.physics_system->GetBodyInterface();

	// Next we can create a rigid body to serve as the floor, we make a large box
	// Create the settings for the collision volume (the shape). 
	// Note that for simple shapes (like boxes) you can also directly construct a BoxShape.
	JPH::BoxShapeSettings floor_shape_settings(JPH::Vec3(100.0f, 1.0f, 100.0f));

	// Create the shape
	JPH::ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
	JPH::ShapeRefC floor_shape = floor_shape_result.Get(); // We don't expect an error here, but you can check floor_shape_result for HasError() / GetError()

	// Create the settings for the body itself. Note that here you can also set other properties like the restitution / friction.
	JPH::BodyCreationSettings floor_settings(floor_shape, JPH::Vec3Arg(0.0, -1.0, 0.0), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING);

	// Create the actual rigid body
	JPH::Body *floor = body_interface.CreateBody(floor_settings); // Note that if we run out of bodies this can return nullptr

	// Add it to the world
	body_interface.AddBody(floor->GetID(), JPH::EActivation::DontActivate);

	// Now create a dynamic body to bounce on the floor
	// Note that this uses the shorthand version of creating and adding a body to the world
	JPH::BodyCreationSettings sphere_settings(new JPH::SphereShape(0.5f), JPH::Vec3Arg(0.0, 2.0, 0.0), JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, Layers::MOVING);
	JPH::BodyID sphere_id = body_interface.CreateAndAddBody(sphere_settings, JPH::EActivation::Activate);

	// Now you can interact with the dynamic body, in this case we're going to give it a velocity.
	// (note that if we had used CreateBody then we could have set the velocity straight on the body before adding it to the physics system)
	body_interface.SetLinearVelocity(sphere_id, JPH::Vec3(0.0f, -5.0f, 0.0f));

    return sphere_id.GetIndexAndSequenceNumber();
}

void PhysicsScene::removeRigidBodyActor(uint32_t body_id) {

}

void PhysicsScene::tick() {
    //Update()
    const float time_step = 1.0f / 60.0f;
    m_physics.physics_system->Update(time_step,
                                                m_physics.m_collision_steps,
                                                m_physics.m_integration_substeps,
                                                m_physics.temp_allocator.get(),
                                                m_physics.job_system.get());
    //remove
}

void PhysicsScene::updateGlobalTransform(TransformComponent *_transf) {
    _transf->setPosition(glm::vec3(1.0f,1.0f,1.0f));
    //_transf->setRotation(glm::vec3(-45.0f,-45.0f,-45.0f));
    
}

}// namespace taixu