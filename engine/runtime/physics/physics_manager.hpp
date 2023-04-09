#ifndef TAIXUENGINE_PHYSICS_MANAGER
#define TAIXUENGINE_PHYSICS_MANAGER




#include "physics_scene.hpp"

namespace taixu
{
class PhysicsManager
{
public:
    PhysicsManager() = default;

    void initialize();

    std::shared_ptr<PhysicsScene> current_scene;
    //std::vector<PhysicsScene>
};

}


#endif /* TAIXUENGINE_PHYSICS_MANAGER */
