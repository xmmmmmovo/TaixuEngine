#ifndef TAIXUENGINE_PHYSICS_SCENE
#define TAIXUENGINE_PHYSICS_SCENE

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
class PhysicsScene
{
public:
    PhysicsScene() = default;
    void initialize();
    void tick();
    void updateGlobalTransform(TransformComponent* _transf);
};

}

#endif /* TAIXUENGINE_PHYSICS_SCENE */
