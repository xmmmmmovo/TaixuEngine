#ifndef TAIXUENGINE_LIGHT
#define TAIXUENGINE_LIGHT

#include "resource/ecs/entity_component/transform/transform_component.hpp"


namespace taixu
{

enum class LightSourseType{
    POINT
    //DIRECTION,
};

struct LightInfo
{
    std::uint32_t light_id;
    glm::vec4 light_position;
    glm::vec4 light_color;
};

class LightSourse
{
public:
    LightSourseType type;
    TransformComponent * transform;
    std::uint32_t unique_id;

    void initialize();
    void SetPosition();
    

};




}

#endif /* TAIXUENGINE_LIGHT */
