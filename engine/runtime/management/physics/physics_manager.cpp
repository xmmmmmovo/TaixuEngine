#include "physics_manager.hpp"

namespace taixu {

void PhysicsManager::init() {
    current_physics_scene = std::make_shared<PhysicsScene>();
    current_physics_scene->init();
}

void PhysicsManager::tick() { current_physics_scene->tick(); }

}// namespace taixu