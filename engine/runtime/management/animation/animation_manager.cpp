#include "animation_manager.hpp"


void taixu::AnimationManager::update(float deltatime) {
    if(_animation_system!=nullptr)
    {
        for (auto const &entity : _animation_system->entities()) {
            if (_current_scene->_ecs_coordinator.anyOf<SkeletonComponent>(
                        entity)) {
                auto &skeleton =
                        _current_scene->_ecs_coordinator
                                .getComponent<SkeletonComponent>(entity);

                skeleton.UpdateAnimation(deltatime);
            }
        }
    }
    
}

void taixu::AnimationManager::bindScene(Scene *scene) {
    _current_scene = scene;
    if (_current_scene != nullptr) {
        auto &coordinator = _current_scene->_ecs_coordinator;
        _animation_system   = coordinator.registerSystem(ANIMATION_SYSTEM_ID);

        {
            Signature animation_signature;
            animation_signature.set(
                    coordinator.getComponentType<TransformComponent>());
            coordinator.setsystemSignature(ANIMATION_SYSTEM_ID,
                                           animation_signature);
        }
    } else {
        _animation_system = nullptr;
    }
}