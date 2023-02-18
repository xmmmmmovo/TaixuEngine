//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_COMPONENT_HPP
#define TAIXUENGINE_COMPONENT_HPP

#include <imgui.h>

namespace taixu::editor {

class IComponent {
protected:
    char const *name{nullptr};

protected:
    IComponent() = default;

public:
    virtual void init() = 0;
    virtual void update()         = 0;

    void setName(char const *cname) { this->name = cname; }
};

}// namespace taixu::editor

#endif//TAIXUENGINE_COMPONENT_HPP
