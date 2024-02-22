//
// Created by xmmmmmovo on 2023/3/29.
//

#ifndef TAIXUENGINE_VIEW_MODEL_HPP
#define TAIXUENGINE_VIEW_MODEL_HPP

#include "ImGuizmo.h"
#include <filesystem>
#include <string>

#include <engine/engine.hpp>
#include <gameplay/gui/window.hpp>

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

    bool is_entity_selected{false};

    std::vector<HierarchyNode<std::string>> useful_objs_hierarchy{};

    std::unique_ptr<Window> window_ptr{nullptr};
    Engine*                 engine_runtime_ptr{nullptr};
};

}// namespace taixu::editor

#endif// TAIXUENGINE_VIEW_MODEL_HPP
