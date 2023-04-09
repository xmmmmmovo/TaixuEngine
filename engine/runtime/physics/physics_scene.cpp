#include "physics_scene.hpp"

namespace taixu
{

void PhysicsScene::initialize() {
    


}

void PhysicsScene::tick() {
    //Update()

    //remove
}

void PhysicsScene::updateGlobalTransform(TransformComponent *_transf) {
    _transf->setPosition(glm::vec3(1.0f,1.0f,1.0f));
    _transf->setRotation(glm::vec3(-45.0f,-45.0f,-45.0f));
    
}

}// namespace taixu