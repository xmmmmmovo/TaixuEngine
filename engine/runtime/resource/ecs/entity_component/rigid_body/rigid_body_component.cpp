#include "rigid_body_component.hpp"

namespace taixu
{
    void RigidBodyComponent::initialize() {



    }

    void RigidBodyComponent::tick() {
        current_scene.lock()->updateGlobalTransform(transform_component);
    }
}

