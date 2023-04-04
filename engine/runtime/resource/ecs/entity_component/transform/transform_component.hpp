#ifndef TAIXUENGINE_TRANSFORM_COMPONENT
#define TAIXUENGINE_TRANSFORM_COMPONENT

#include <string>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/matrix.hpp>
#include "resource/ecs/entity_component/entity_component.hpp"
namespace taixu
{
class TransformComponent
{
public:
TransformComponent()=default;
glm::vec3 position{0.f,0.f,0.f};
glm::vec3 scale{1.f,1.f,1.f};
glm::vec3 rotation_degrees{0.f,0.f,0.f};
glm::mat4 transform{glm::mat4(1.0f)};
//glm::mat4 lastTransform{glm::mat4(1.0f)};

TransformComponent(glm::vec3 pos,glm::vec3 scale,glm::vec3 rotate)
:position(pos),scale(scale),rotation_degrees(rotate){}


void setPosition(glm::vec3 pos);
void setScale(glm::vec3 scl);
void setRotation(glm::vec3 rotate);
glm::mat4 getTransformMatrix();
void makeTransformMatrix();

};
}

#endif /* TAIXUENGINE_TRANSFORM_COMPONENT */
