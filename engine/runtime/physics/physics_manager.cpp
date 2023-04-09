#include "physics_manager.hpp"

namespace taixu
{
void PhysicsManager::initialize() {
    current_scene = std::make_shared<PhysicsScene>();
    current_scene->initialize();
}
}