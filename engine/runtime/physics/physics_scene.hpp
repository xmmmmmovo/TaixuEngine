#ifndef TAIXUENGINE_PHYSICS_SCENE
#define TAIXUENGINE_PHYSICS_SCENE

//#include <Jolt/Jolt.h>
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
