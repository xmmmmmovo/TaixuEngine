#ifndef TAIXUENGINE_ECS_Light_COMPONENT
#define TAIXUENGINE_ECS_Light_COMPONENT

#include <glm/glm.hpp>

#include "light_source_type.hpp"

namespace taixu {

class LightComponent {
public:
    LightSourseType type{LightSourseType::INVALID};
    glm::vec4       light_color{glm::vec4(0.0, 0.0, 0.0, 1.0)};
};

}// namespace taixu
#endif /* TAIXUENGINE_ECS_Light_COMPONENT */
