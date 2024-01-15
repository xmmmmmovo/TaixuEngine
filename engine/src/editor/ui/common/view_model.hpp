//
// Created by xmmmmmovo on 2023/3/29.
//

#ifndef TAIXUENGINE_VIEW_MODEL_HPP
#define TAIXUENGINE_VIEW_MODEL_HPP

#include "ImGuizmo.h"
#include "engine/engine.hpp"
#include "management/ecs/core/ecs_types.hpp"
#include "management/ecs/object/game_object.hpp"
#include <filesystem>
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
private:
    EngineContext const* engine_context_ptr{nullptr};

public:
    std::filesystem::path                             project_path{};
    std::filesystem::path                             selected_path{};
    HierarchyNode<std::filesystem::path>*             selected_node{nullptr};
    std::vector<HierarchyNode<std::filesystem::path>> path_hierarchy{};

    ImGuizmo::MODE      guizmo_mode{ImGuizmo::MODE::LOCAL};
    ImGuizmo::OPERATION guizmo_operation{ImGuizmo::OPERATION::TRANSLATE};

    Entity selected_entity{0};
    bool   is_entity_selected{false};

    std::vector<HierarchyNode<std::string>> useful_objs_hierarchy{};

    void init(const Engine* engine) {
        this->engine_context_ptr = &engine->context();
    }

    EngineContext const* getEngineContext() const {
        return this->engine_context_ptr;
    }
};

}// namespace taixu::editor

#endif// TAIXUENGINE_VIEW_MODEL_HPP
