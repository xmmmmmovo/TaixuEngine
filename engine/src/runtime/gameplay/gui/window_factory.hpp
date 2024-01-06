//
// Created by xmmmmmovo on 11/21/2023.
//

#ifndef ENGINE_SRC_RUNTIME_GAMEPLAY_GUI_WINDOW_FACTORY_926712A089BE46CE8ADDFA415AE61838
#define ENGINE_SRC_RUNTIME_GAMEPLAY_GUI_WINDOW_FACTORY_926712A089BE46CE8ADDFA415AE61838

#include <memory>
#include <string>

#include "common/base/core.hpp"
#include "common/base/macro.hpp"
#include "common/designs/abstract_factory.hpp"
#include "common/log/logger.hpp"
#include "window.hpp"

namespace taixu {

class WindowFactory : private Noncopyable,
                      public AbstractFactory<WindowAPI, Window> {
    using create_window_func_t = std::function<std::unique_ptr<Window>()>;

private:
    TX_INLINE static std::unordered_map<RenderAPI, WindowAPI>
            _render_api_window_mapping{};

public:
    static std::unique_ptr<Window> createWindow(RenderAPI render_api) {
        return createProduct(getRenderAPIMappedWindowAPI(render_api));
    }

    static void registerRenderAPI(RenderAPI render_api, WindowAPI window_api) {
        auto iter = _render_api_window_mapping.find(render_api);
        if (iter != _render_api_window_mapping.end()) {
            WARN_LOG("This render api have already registered");
            iter->second = window_api;
        } else {
            _render_api_window_mapping[render_api] = window_api;
        }
    }

private:
    static WindowAPI getRenderAPIMappedWindowAPI(RenderAPI render_api) {
        auto iter = _render_api_window_mapping.find(render_api);
        if (iter != _render_api_window_mapping.end()) {
            return iter->second;
        } else {
            FATAL_LOG("Cannot find this render api!");
            return WindowAPI::NONE;
        }
    }
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_GAMEPLAY_GUI_WINDOW_FACTORY_926712A089BE46CE8ADDFA415AE61838
