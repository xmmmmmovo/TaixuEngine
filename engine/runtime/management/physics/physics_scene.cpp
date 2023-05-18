#include "physics_scene.hpp"

namespace taixu {

void PhysicsScene::init() {
    // Register allocation hook
    RegisterDefaultAllocator();
    JPH::Factory::sInstance = new JPH::Factory();
    JPH::RegisterTypes();

    m_physics.physics_system = std::make_unique<JPH::PhysicsSystem>();

    m_physics.job_system = std::make_unique<JPH::JobSystemThreadPool>(
            m_parameter.m_max_job_count, m_parameter.m_max_barrier_count,
            static_cast<int>(m_parameter.m_max_concurrent_job_count));

    m_physics.temp_allocator =
            std::make_unique<JPH::TempAllocatorImpl>(10 * 1024 * 1024);
    m_physics.broad_phase_layer_interface =
            std::make_unique<BPLayerInterfaceImpl>();

    m_physics.physics_system->Init(
            m_parameter.m_max_body_count, m_parameter.m_body_mutex_count,
            m_parameter.m_max_body_pairs, m_parameter.m_max_contact_constraints,
            *(m_physics.broad_phase_layer_interface),
            object_vs_broadphase_layer_filter, object_vs_object_layer_filter);

    // use the default setting
    m_physics.physics_system->SetPhysicsSettings(JPH::PhysicsSettings());

    m_physics.physics_system->SetGravity(JPH::Vec3(0.f, -0.8f, 0.f));

    m_physics.body_activation_listener =
            std::make_unique<MyBodyActivationListener>();
    m_physics.physics_system->SetBodyActivationListener(
            m_physics.body_activation_listener.get());

    m_physics.contact_listener = std::make_unique<MyContactListener>();
    m_physics.physics_system->SetContactListener(
            m_physics.contact_listener.get());


    //add components
}

JPH::BodyID PhysicsScene::createRigidBodyActor(const RigidbodyInfo &rgdInfo) {
    JPH::Shape         *shape = toShape(rgdInfo.stype, rgdInfo.scale);
    JPH::BodyInterface &body_interface =
            m_physics.physics_system->GetBodyInterface();
    JPH::BodyCreationSettings shape_settings;
    //only DYNAMIC and STATIC
    if (rgdInfo.mtype == MotionType::DYNAMIC) {
        shape_settings = JPH::BodyCreationSettings(
                shape,
                JPH::Vec3Arg(rgdInfo.position.x, rgdInfo.position.y,
                             rgdInfo.position.z),
                JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic,
                layers::MOVING);
    } else {
        shape_settings = JPH::BodyCreationSettings(
                shape,
                JPH::Vec3Arg(rgdInfo.position.x, rgdInfo.position.y,
                             rgdInfo.position.z),
                JPH::Quat::sIdentity(), JPH::EMotionType::Static,
                layers::NON_MOVING);
    }
    JPH::BodyID body_id = body_interface.CreateAndAddBody(
            shape_settings, JPH::EActivation::Activate);
    current_bodies.push_back(body_id);
    return body_id;
}

void PhysicsScene::createRigidBodyActor() {
    // The main way to interact with the bodies in the physics system is through the body interface. There is a locking and a non-locking
    // variant of this. We're going to use the locking version (even though we're not planning to access bodies from multiple threads)
    JPH::BodyInterface &body_interface =
            m_physics.physics_system->GetBodyInterface();

    // Next we can create a rigid body to serve as the floor, we make a large box
    // Create the settings for the collision volume (the shape).
    // Note that for simple shapes (like boxes) you can also directly construct a BoxShape.
    JPH::BoxShapeSettings floor_shape_settings(JPH::Vec3(100.0f, 0.1f, 100.0f));

    // Create the shape
    JPH::ShapeSettings::ShapeResult floor_shape_result =
            floor_shape_settings.Create();
    JPH::ShapeRefC floor_shape =
            floor_shape_result
                    .Get();// We don't expect an error here, but you can check floor_shape_result for HasError() / GetError()

    // Create the settings for the body itself. Note that here you can also set other properties like the restitution / friction.
    JPH::BodyCreationSettings floor_settings(
            floor_shape, JPH::Vec3Arg(0.0, 0.0, 0.0), JPH::Quat::sIdentity(),
            JPH::EMotionType::Static, layers::NON_MOVING);

    // Create the actual rigid body
    JPH::Body *floor = body_interface.CreateBody(
            floor_settings);// Note that if we run out of bodies this can return nullptr

    // Add it to the world
    body_interface.AddBody(floor->GetID(), JPH::EActivation::Activate);

    // Now create a dynamic body to bounce on the floor
    // Note that this uses the shorthand version of creating and adding a body to the world
    JPH::BodyCreationSettings sphere_settings(
            new JPH::SphereShape(0.5f), JPH::Vec3Arg(0.0, 4.0, 0.0),
            JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic, layers::MOVING);
    sphere_id = body_interface.CreateAndAddBody(sphere_settings,
                                                JPH::EActivation::Activate);

    // Now you can interact with the dynamic body, in this case we're going to give it a velocity.
    // (note that if we had used CreateBody then we could have set the velocity straight on the body before adding it to the physics system)
    body_interface.SetLinearVelocity(sphere_id, JPH::Vec3(0.0f, 0.0f, 0.0f));

    //return sphere_id.GetIndexAndSequenceNumber();
}

void PhysicsScene::removeRigidBodyActor(JPH::BodyID body_id) {}

// void PhysicsScene::bindScene(ECSCoordinator *scene) {
//     ecsInterface = scene;
//     auto test = ecsInterface->getComponent<RigidBodyComponent>(0);
// }

void PhysicsScene::update() {
    //Update()
    JPH::BodyInterface &body_interface =
            m_physics.physics_system->GetBodyInterface();
    //assert(body_interface.IsActive(sphere_id)==false);

    const float time_step = 1.0f / 60.0f;

    //for debug
    // step++;
    // Vec3 position = body_interface.GetCenterOfMassPosition(sphere_id);
    // Vec3 velocity = body_interface.GetLinearVelocity(sphere_id);

    // spdlog::debug("Step {}: Position = ( {} , {}, {} ), Velocity = ( {}, {}, {} )",
    // step,position.GetX(),
    // position.GetY(),
    // position.GetZ(),
    // velocity.GetX(),
    // velocity.GetY(),
    // velocity.GetZ());

    m_physics.physics_system->Update(time_step, m_physics.m_collision_steps,
                                     m_physics.m_integration_substeps,
                                     m_physics.temp_allocator.get(),
                                     m_physics.job_system.get());
    //remove
}

void PhysicsScene::updateGlobalTransform(TransformComponent *_transf,
                                         JPH::BodyID         body_id) {
    //_transf->setPosition(glm::vec3(1.0f,1.0f,1.0f));
    //_transf->setRotation(glm::vec3(-45.0f,-45.0f,-45.0f));
    JPH::BodyInterface &body_interface =
            m_physics.physics_system->GetBodyInterface();
    Vec3 position = body_interface.GetCenterOfMassPosition(body_id);
    Vec3 velocity = body_interface.GetLinearVelocity(body_id);
    _transf->set_position(
            glm::vec3(position.GetX(), position.GetY(), position.GetZ()));
    _transf->setRotation(glm::vec3(glm::degrees(position.GetX()),
                                   glm::degrees(position.GetY()),
                                   glm::degrees(position.GetZ())));
}

JPH::Shape *PhysicsScene::toShape(RigidBodyShapeType shape,
                                  const glm::vec3   &scale) {

    //all shapes define to indentity size
    JPH::Shape *jph_shape = nullptr;
    if (shape == RigidBodyShapeType::BOX) {
        JPH::Vec3 jph_box(scale.x, scale.y, scale.z);
        jph_shape = new JPH::BoxShape(jph_box, 0.f);
    } else if (shape == RigidBodyShapeType::SPHERE) {
        jph_shape = new JPH::SphereShape((scale.x + scale.y + scale.z) / 3 * 1);
    } else {
        spdlog::debug("Unsupported Shape");
    }

    return jph_shape;
}

}// namespace taixu