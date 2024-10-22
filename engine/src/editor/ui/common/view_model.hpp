//
// Created by xmmmmmovo on 2023/3/29.
//

#ifndef TAIXUENGINE_VIEW_MODEL_HPP
#define TAIXUENGINE_VIEW_MODEL_HPP

#include <filesystem>

#include <imgui.h>
#include <imgui/imzmo/ImGuizmo.h>

#include "file_watcher.hpp"
#include "hierarchy_struct.hpp"

namespace taixu::editor {

enum class MovingState { SELECT, MOVING };

struct ViewModel {
    FileTreeNodeT  file_component_hierarchy{};
    FileTreeNodeT* selected_node{nullptr};

    MovingState moving_state{MovingState::MOVING};

    ImGuizmo::MODE      guizmo_mode{ImGuizmo::MODE::LOCAL};
    ImGuizmo::OPERATION guizmo_operation{ImGuizmo::OPERATION::TRANSLATE};

    bool is_entity_selected{false};
};

}// namespace taixu::editor

#endif// TAIXUENGINE_VIEW_MODEL_HPP
