#ifndef TAIXUENGINE_LIGHT
#define TAIXUENGINE_LIGHT

#include "resource/ecs/entity_component/transform/transform_component.hpp"


namespace taixu
{

enum class LightSourseType{
    POINT
    //DIRECTION,
};

class LightSourse
{
public:
    LightSourse() = default;
    LightSourseType type;
    TransformComponent * transform;
    glm::vec4 light_color;
    std::uint32_t unique_id;

    void initialize();
    void setPosition(const glm::vec3 &pos);
    void setcolor(const glm::vec4 &pos);
    

};




}

#endif /* TAIXUENGINE_LIGHT */
