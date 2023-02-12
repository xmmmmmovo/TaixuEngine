//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_CONTROL_COMPONENT_HPP
#define TAIXUENGINE_CONTROL_COMPONENT_HPP

#include "interface/component.hpp"

namespace taixu::editor {
class ControlComponent : public IComponent {
public:
    void init() override;
    void render() override;
};
}// namespace taixu::editor

#endif//TAIXUENGINE_CONTROL_COMPONENT_HPP
