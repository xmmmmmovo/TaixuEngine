/*
 Copyright (c) xmmmmmovo@2024.
 */

#pragma once

#include <vector>

namespace taixu::editor {

template<typename DataT>
struct HierarchyDataNode {
    DataT data{};
};

template<typename ChildT>
struct ChildrensHierarchyNode {
    std::vector<ChildT> childerns{};
};

template<typename DataT, typename ChildT>
struct ChildrensHierarchyDataNode : public HierarchyDataNode<DataT>, public ChildrensHierarchyNode<ChildT> {};

template<typename DataT>
struct ChildrensSameHierarchyNode : public HierarchyDataNode<DataT>,
                                    public ChildrensHierarchyNode<ChildrensSameHierarchyNode<DataT>> {};

template<typename DataT, typename ChildT, size_t ArrSize>
struct ChildrensArrayHierarchyDataNode : public HierarchyDataNode<DataT> {
    std::array<ChildT, ArrSize> childerns{};
};

}// namespace taixu::editor
