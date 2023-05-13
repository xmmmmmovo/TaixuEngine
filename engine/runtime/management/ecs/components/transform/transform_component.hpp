#ifndef TAIXUENGINE_TRANSFORM_COMPONENT
#define TAIXUENGINE_TRANSFORM_COMPONENT

#include <string>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/matrix.hpp"

namespace taixu {
class TransformComponent {
public:
    glm::vec3 _position{0.f, 0.f, 0.f};
    glm::vec3 _scale{1.f, 1.f, 1.f};
    glm::vec3 _rotation{0.0f, 0.0f, 0.0f};
    glm::mat4 transform{glm::mat4(1.0f)};

    TransformComponent() = default;
    template<typename T>
    explicit TransformComponent(T &&pos, T &&scale, T &&rotate)
        : _position(std::forward<T>(pos)), _scale(std::forward<T>(scale)),
          _rotation(std::forward<T>(rotate)) {}

    void setPosition(glm::vec3 pos);
    void setScale(glm::vec3 scl);
    void setRotation(glm::vec3 rotate);
    glm::mat4 getTransformMatrix();
    void makeTransformMatrix();
};
}// namespace taixu

#endif /* TAIXUENGINE_TRANSFORM_COMPONENT */
