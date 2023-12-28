#ifndef TAIXUENGINE_TRANSFORM_COMPONENT
#define TAIXUENGINE_TRANSFORM_COMPONENT

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

#include "common/base/macro.hpp"

namespace taixu {

class TransformComponent {
    PROTOTYPE_DFT(private, glm::vec3, translate, glm::vec3(0.0f));
    PROTOTYPE_DFT(private, glm::vec3, scale, glm::vec3(1.0f));
    PROTOTYPE_DFT(private, glm::quat, rotation,
                  glm::quat(1.0f, 0.0f, 0.0f, 0.0f));

    PROTOTYPE_DFT(private, glm::mat4, transform, glm::mat4(1.0f));

    PROTOTYPE_DFT(private, bool, inversed, false);

public:
    TransformComponent() = default;

    template<typename T, typename RT>
    explicit TransformComponent(T&& pos, T&& scale, RT&& rotate)
        : _translate(std::forward<T>(pos)), _scale(std::forward<T>(scale)),
          _rotation(std::forward<RT>(rotate)) {}

    void makeTransformMatrix() {
        glm::mat4 const translation_matrix =
                glm::translate(glm::mat4(1.0f), _translate);
        glm::mat4 const rotation_matrix = glm::toMat4(_rotation);
        glm::mat4 const scaling_matrix  = glm::scale(glm::mat4(1.0f), _scale);
        _transform = translation_matrix * rotation_matrix * scaling_matrix;
    }
};
}// namespace taixu

#endif /* TAIXUENGINE_TRANSFORM_COMPONENT */
