//
// Created by xmmmmmovo on 2023/5/4.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_RENDERABLE_RENDERABLE_COMPONENT_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_RENDERABLE_RENDERABLE_COMPONENT_HPP

#include "resource/res_type/raw_data/material.hpp"
#include "resource/res_type/raw_data/model.hpp"

namespace taixu {

class RenderableComponent {
public:
    bool   visiable{true};
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_RENDERABLE_RENDERABLE_COMPONENT_HPP
