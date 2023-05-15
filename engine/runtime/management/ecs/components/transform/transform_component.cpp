#include "transform_component.hpp"

namespace taixu{

void TransformComponent::setPosition(glm::vec3 pos) {_position=pos;}

void TransformComponent::addPosition(glm::vec3 pos) {_position += pos;}

void TransformComponent::setScale(glm::vec3 scl) {_scale = scl;}

void TransformComponent::Scale(glm::vec3 scl) {_scale *= scl;}


void TransformComponent::setRotation(glm::vec3 rotate) {_rotation = rotate;}

void TransformComponent::setRotation(glm::quat q) {
    glm::mat4 rotation = glm::mat4_cast(q);
    float x,y,z;
    glm::extractEulerAngleXYZ(rotation,x,y,z);
    _rotation = glm::vec3(x,y,z);
}

void TransformComponent::setRotation(glm::mat4 r) {
    float x=0,y=0,z=0;
    glm::extractEulerAngleXYZ(r,x,y,z);
    
    
     _rotation.x += glm::degrees(x);
     _rotation.y += glm::degrees(y);
     _rotation.z += glm::degrees(z);
     if(x>0.5)
         int a=0;

}

glm::mat4 TransformComponent::getTransformMatrix(){return transform;}
void TransformComponent::makeTransformMatrix() { 
    //scale
    transform = glm::mat4 (1.0f);
    transform=glm::scale(transform,_scale);
    //rotation
    glm::quat rotation {1.0f, 0.0f, 0.0f, 0.0f};
    glm::quat rotateX = glm::angleAxis(glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::quat rotateY = glm::angleAxis(glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::quat rotateZ = glm::angleAxis(glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    rotation = rotateZ * rotateY * rotateX;
    glm::mat4 RotationMatrix = glm::mat4_cast(rotation);
    //tranlation
    glm::mat4 TranslateMatrix = glm::mat4(1.0f);
    TranslateMatrix = glm::translate(TranslateMatrix,_position);

    transform=TranslateMatrix*RotationMatrix*transform;
   
}   

}// namespace taixu