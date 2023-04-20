#include "light.hpp"

namespace taixu
{


void LightSourse::initialize() {
    
}

void LightSourse::setPosition(const glm::vec3 &pos) {
    transform->setPosition(pos);
}

void LightSourse::setcolor(const glm::vec4 &color) {
    light_color = color;
}

}// namespace taixu