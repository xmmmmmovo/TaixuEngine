#include "physics_manager.hpp"

namespace taixu {

void PhysicsManager::init() {
    current_physics_scene = std::make_shared<PhysicsScene>();
    current_physics_scene->init();

}

void PhysicsManager::update() { 
    current_physics_scene->update();
    //for(auto const&entity : ) 
}

}// namespace taixu