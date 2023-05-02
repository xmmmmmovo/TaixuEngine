#ifndef TAIXUENGINE_PHYSICS_MANAGER
#define TAIXUENGINE_PHYSICS_MANAGER

#include "physics_scene.hpp"

namespace taixu {

class PhysicsManager {
public:
    PhysicsManager() = default;

    void init();

    void tick();

    std::shared_ptr<PhysicsScene> current_scene;
};

}// namespace taixu


#endif /* TAIXUENGINE_PHYSICS_MANAGER */
