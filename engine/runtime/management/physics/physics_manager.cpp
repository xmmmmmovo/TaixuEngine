#include "physics_manager.hpp"
#include "management/ecs/components/transform/transform_component.hpp"

namespace taixu {

void PhysicsManager::init() {

    _physics_scene = std::make_shared<PhysicsScene>();
    _physics_scene->init();
}

void PhysicsManager::update() { _physics_scene->update(); }

void PhysicsManager::bindScene(Scene *scene) {
    _current_scene = scene;
    if (_current_scene != nullptr) {
        auto &coordinator = _current_scene->_ecs_coordinator;
        _physics_system   = coordinator.registerSystem(PHYSICS_SYSTEM_ID);

        {
            Signature physics_signature;
            physics_signature.set(
                    coordinator.getComponentType<TransformComponent>());
            coordinator.setsystemSignature(PHYSICS_SYSTEM_ID,
                                           physics_signature);
        }
    } else {
        _physics_system = nullptr;
    }

}

}// namespace taixu