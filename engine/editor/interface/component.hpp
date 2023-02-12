//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_COMPONENT_HPP
#define TAIXUENGINE_COMPONENT_HPP

namespace taixu::editor {

class IComponent {
public:
    virtual void init()   = 0;
    virtual void render() = 0;
};

}// namespace taixu::editor

#endif//TAIXUENGINE_COMPONENT_HPP
