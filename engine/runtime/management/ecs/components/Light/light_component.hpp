#ifndef TAIXUENGINE_Light_COMPONENT
#define TAIXUENGINE_Light_COMPONENT

#include "glm/glm.hpp"

namespace taixu
{
    enum class LightSourseType{
    POINT
    //DIRECTION,
    };

class LightComponent
{
public:
    LightComponent() = default;
    LightSourseType type;
    glm::vec3 light_color;

    void setcolor(const glm::vec3 &color)
    {
        light_color = color;
    }
};



}
#endif /* TAIXUENGINE_Light_COMPONENT */
