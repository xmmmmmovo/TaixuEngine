//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_RENDER_COMPONENT_HPP
#define TAIXUENGINE_RENDER_COMPONENT_HPP

#include "interface/component.hpp"
#include "graphics/renderer.hpp"
namespace taixu::editor {
class RenderComponent : public IComponent {
public:
    void init() override;
    void update() override;

private:
    std::shared_ptr<cg::Renderer> m_renderer;
};

}

#endif//TAIXUENGINE_RENDER_COMPONENT_HPP
