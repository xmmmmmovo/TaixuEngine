//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include "interface/component.hpp"

namespace taixu::editor {
class RenderComponent : public IComponent {
public:
    void init() override;
    void render() override;
};

}

#endif//TAIXUENGINE_RENDER_COMPONENT_HPP
