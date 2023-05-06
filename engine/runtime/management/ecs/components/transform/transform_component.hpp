#ifndef TAIXUENGINE_TRANSFORM_COMPONENT
#define TAIXUENGINE_TRANSFORM_COMPONENT

#include <string>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/matrix.hpp"

namespace taixu {
class TransformComponent {
public:
    glm::vec3 position{0.f, 0.f, 0.f};
    glm::vec3 scale{1.f, 1.f, 1.f};
    glm::quat rotation{glm::quat(1.0f, 0.0f, 0.0f, 0.0f)};

    explicit TransformComponent(glm::vec3 const &pos, glm::vec3 const &scale,
                                glm::quat const &rotate)
        : position(pos), scale(scale), rotation(rotate) {}
};
}// namespace taixu

#endif /* TAIXUENGINE_TRANSFORM_COMPONENT */
