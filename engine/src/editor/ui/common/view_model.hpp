//
// Created by xmmmmmovo on 2023/3/29.
//

#ifndef TAIXUENGINE_VIEW_MODEL_HPP
#define TAIXUENGINE_VIEW_MODEL_HPP

#include <filesystem>
#include <string>

#include <imgui.h>

#include "imgui/imzmo/ImGuizmo.h"

namespace taixu::editor {

struct HierarchyNode {
    std::string name{};
};

template<typename DataT>
struct HierarchyDataNode : public HierarchyNode {
    DataT data{};
};

template<typename ChildT>
struct ChildrensHierarchyNode : public HierarchyNode {
    std::vector<ChildT> childerns{};
    bool                expanded{false};
};

template<typename ChildT, typename DataT>
struct ChildrensHierarchyDataNode : public HierarchyDataNode<DataT> {
    std::vector<ChildT> childerns{};
    bool                expanded{false};
};

template<typename ChildT, size_t ArrSize>
struct ChildrensArrayHierarchyNode : public HierarchyNode {
    std::array<ChildT, ArrSize> childerns{};
    bool                        expanded{false};
};

template<typename ChildT, size_t ArrSize, typename DataT>
struct ChildrensArrayHierarchyDataNode : public HierarchyDataNode<DataT> {
    std::array<ChildT, ArrSize> childerns{};
    bool                        expanded{false};
};

struct ViewModel {
    std::filesystem::path project_path{};
    std::filesystem::path selected_path{};
    // HierarchyNode<std::filesystem::path>*             selected_node{nullptr};
    // std::vector<HierarchyNode<std::filesystem::path>> path_hierarchy{};

    ImGuizmo::MODE      guizmo_mode{ImGuizmo::MODE::LOCAL};
    ImGuizmo::OPERATION guizmo_operation{ImGuizmo::OPERATION::TRANSLATE};

    bool is_entity_selected{false};
};

}// namespace taixu::editor

#endif// TAIXUENGINE_VIEW_MODEL_HPP
