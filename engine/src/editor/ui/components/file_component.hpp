//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_FILE_COMPONENT_HPP
#define TAIXUENGINE_FILE_COMPONENT_HPP

#include "ui/common/ui_component.hpp"
#include "ui/common/view_model.hpp"

namespace taixu::editor {

class FileComponent final : public AbstractUIComponent {
private:
    void recursiveBuildFileTree(FileTreeNodeT& node);
    void buildFileTree();
    void buildShowItems(std::vector<FileTreeNodeT>& nodes) const;
    void buildDirShowcase() const;

public:
    explicit FileComponent(ViewModel& view_model)
        : AbstractUIComponent(view_model) {}

    void update();
};
}// namespace taixu::editor

#endif// TAIXUENGINE_FILE_COMPONENT_HPP
