//
// Created by xmmmmmovo on 2023/5/4.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_RENDERABLE_RENDERABLE_COMPONENT_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_RENDERABLE_RENDERABLE_COMPONENT_HPP

#include "management/ecs/object/abstract_component.hpp"
#include "management/graphics/render/vertex_array.hpp"
#include "resource/raw_data/material.hpp"
#include "resource/raw_data/model.hpp"

namespace taixu {

class RenderableComponent {
public:
    Model *model{nullptr};
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_ENTITY_COMPONENT_RENDERABLE_RENDERABLE_COMPONENT_HPP
