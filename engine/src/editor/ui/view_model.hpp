//
// Created by xmmmmmovo on 2023/3/29.
//

#ifndef TAIXUENGINE_VIEW_MODEL_HPP
#define TAIXUENGINE_VIEW_MODEL_HPP

#include <ImGuizmo.h>
#include <filesystem>
#include <runtime/engine.hpp>
#include <runtime/management/ecs/core/ecs_types.hpp>
#include <runtime/management/ecs/object/game_object.hpp>
#include <runtime/management/graphics/renderer.hpp>
#include <string>

namespace taixu::editor {

template<typename Data>
struct HierarchyNode {
    std::string                      name{};
    bool                             expanded{false};
    Data                             data{};
    std::vector<HierarchyNode<Data>> children{};
};

struct ViewModel {
    std::filesystem::path                             project_path{};
    std::filesystem::path                             selected_path{};
    HierarchyNode<std::filesystem::path>*             selected_node{nullptr};
    std::vector<HierarchyNode<std::filesystem::path>> path_hierarchy{};

    ImGuizmo::MODE      guizmo_mode{ImGuizmo::MODE::LOCAL};
    ImGuizmo::OPERATION guizmo_operation{ImGuizmo::OPERATION::TRANSLATE};

    Entity selected_entity{0};
    bool   is_entity_selected{false};

    std::vector<HierarchyNode<std::string>> useful_objs_hierarchy{};

    Engine*           engine_runtime_ptr{nullptr};
    AbstractRenderer* renderer{nullptr};

    IFrameBuffer* framebuffer{nullptr};
};

}// namespace taixu::editor

#endif// TAIXUENGINE_VIEW_MODEL_HPP
