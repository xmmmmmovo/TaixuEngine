//
// Created by xmmmmmovo on 2023/3/29.
//

#ifndef TAIXUENGINE_VIEW_MODEL_HPP
#define TAIXUENGINE_VIEW_MODEL_HPP

#include "ImGuizmo.h"
#include "engine.hpp"
#include "management/ecs/components/transform/transform_component.hpp"
#include "management/ecs/core/ecs_types.hpp"
#include "management/ecs/object/game_object.hpp"
#include "management/graphics/renderer.hpp"
#include <filesystem>
#include <string>

namespace taixu::editor {

template<typename Child>
struct HierarchyNode {
    bool                              have_child{false};
    std::vector<HierarchyNode<Child>> children{};
};

struct ViewModel {
    std::filesystem::path project_path;
    std::filesystem::path dir_path;

    ImGuizmo::MODE      guizmo_mode{ImGuizmo::MODE::LOCAL};
    ImGuizmo::OPERATION guizmo_operation{ImGuizmo::OPERATION::TRANSLATE};

    Entity selected_entity{0};
    bool   is_entity_selected{false};

    Engine           *engine_runtime_ptr{nullptr};
    AbstractRenderer *renderer{nullptr};

    IFrameBuffer *framebuffer{nullptr};
};

}// namespace taixu::editor

#endif//TAIXUENGINE_VIEW_MODEL_HPP
