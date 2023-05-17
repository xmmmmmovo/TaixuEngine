#ifndef TAIXUENGINE_PHYSICS_MANAGER
#define TAIXUENGINE_PHYSICS_MANAGER

#include "physics_scene.hpp"
#include "management/ecs/system/system.hpp"
namespace taixu {
class Scene;
class PhysicsManager {
public:
    PhysicsManager() = default;

    void init();

    void update();

    //System *_physics_system{nullptr};
    //static constexpr SystemIdType PHYSICS_SYSTEM_ID = "physics"_hash64;
    std::shared_ptr<PhysicsScene> current_physics_scene;
};

}// namespace taixu


#endif /* TAIXUENGINE_PHYSICS_MANAGER */
