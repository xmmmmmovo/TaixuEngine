#ifndef TAIXUENGINE_TRANSFORM_COMPONENT
#define TAIXUENGINE_TRANSFORM_COMPONENT

#include <string>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/matrix.hpp"

#include "core/base/macro.hpp"

namespace taixu {
class TransformComponent {
    PROTOTYPE(private, glm::vec3, position);
    PROTOTYPE(private, glm::vec3, scale);
    PROTOTYPE(private, glm::quat, rotation);

    PROTOTYPE(private, glm::vec3, eular_rotation);

    PROTOTYPE(private, glm::mat4, transform);

public:
    TransformComponent() = default;
    template<typename T>
    explicit TransformComponent(T &&pos, T &&scale, T &&rotate)
        : _position(std::forward<T>(pos)), _scale(std::forward<T>(scale)),
          _rotation(std::forward<T>(rotate)) {}

    void addPosition(glm::vec3 pos) { _position += pos; }
    void applyScale(glm::vec3 scl) { _scale *= scl; }

    void setRotation(glm::vec3 rotate) {
        _rotation.x = rotate.x;
        _rotation.y = rotate.y;
        _rotation.z = rotate.z;
    }

    void setRotation(glm::mat4 r) {
        float x = 0, y = 0, z = 0;
        glm::extractEulerAngleXYZ(r, x, y, z);

        _rotation.x += glm::degrees(x);
        _rotation.y += glm::degrees(y);
        _rotation.z += glm::degrees(z);
    }

    void makeTransformMatrix() {
        {
            //scale
            _transform = glm::mat4(1.0f);
            _transform = glm::scale(_transform, _scale);
            //rotation
            glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};
            glm::quat rotateX        = glm::angleAxis(glm::radians(_rotation.x),
                                                      glm::vec3(1.0f, 0.0f, 0.0f));
            glm::quat rotateY        = glm::angleAxis(glm::radians(_rotation.y),
                                                      glm::vec3(0.0f, 1.0f, 0.0f));
            glm::quat rotateZ        = glm::angleAxis(glm::radians(_rotation.z),
                                                      glm::vec3(0.0f, 0.0f, 1.0f));
            rotation                 = rotateZ * rotateY * rotateX;
            glm::mat4 RotationMatrix = glm::mat4_cast(rotation);
            //tranlation
            glm::mat4 TranslateMatrix = glm::mat4(1.0f);
            TranslateMatrix = glm::translate(TranslateMatrix, _position);

            _transform = TranslateMatrix * RotationMatrix * _transform;
        }
    }
};
}// namespace taixu

#endif /* TAIXUENGINE_TRANSFORM_COMPONENT */
