//
// Created by xmmmmmovo on 2023/2/12.
//

#ifndef TAIXUENGINE_UI_COMPONENT_HPP
#define TAIXUENGINE_UI_COMPONENT_HPP

#include "common/designs/noncopyable.hpp"
#include "view_model.hpp"

namespace taixu::editor {

#define ICON_ENTRY(ICON, STR) ICON " " STR

/**
 * @brief UI component interface
 */
class AbstractUIComponent : Noncopyable {
protected:
    ViewModel* _view_model{nullptr};

    ImGuiComponentInfo const _component_info{};
    TX_INLINE static bool    enable{false};

public:
    explicit AbstractUIComponent(ViewModel*                view_model,
                                 ImGuiComponentInfo const& component_info)
        : _view_model(view_model), _component_info(component_info) {}

    [[nodiscard]] ImGuiComponentInfo const& getComponentInfo() const {
        return _component_info;
    }
};

}// namespace taixu::editor

#endif// TAIXUENGINE_UI_COMPONENT_HPP
