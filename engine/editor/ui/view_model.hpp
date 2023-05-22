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

template<typename Data>
struct HierarchyNode {
    std::string                      name{};
    Data                             data{};
    std::vector<HierarchyNode<Data>> children{};
};

struct ViewModel {
    std::filesystem::path                project_path;
    std::filesystem::path                dir_path;
    HierarchyNode<std::filesystem::path> path_hierarchy{};

    ImGuizmo::MODE      guizmo_mode{ImGuizmo::MODE::LOCAL};
    ImGuizmo::OPERATION guizmo_operation{ImGuizmo::OPERATION::TRANSLATE};

    Entity selected_entity{0};
    bool   is_entity_selected{false};

    HierarchyNode<std::string> useful_objs_hierarchy{};

    Engine           *engine_runtime_ptr{nullptr};
    AbstractRenderer *renderer{nullptr};

    IFrameBuffer *framebuffer{nullptr};
};

}// namespace taixu::editor

#endif//TAIXUENGINE_VIEW_MODEL_HPP
