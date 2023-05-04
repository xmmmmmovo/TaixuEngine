#include "physics_manager.hpp"

namespace taixu {

void PhysicsManager::init() {
    current_scene = std::make_shared<PhysicsScene>();
    current_scene->init();
}

void PhysicsManager::tick() { current_scene->tick(); }

}// namespace taixu