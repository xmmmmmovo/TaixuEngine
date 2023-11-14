//
// Created by xmmmmmovo on 11/12/2023.
//

#ifndef ENGINE_SRC_RUNTIME_ENGINE_CONTEXT_AFC9470FE8DF4FD682C297E3488583D5
#define ENGINE_SRC_RUNTIME_ENGINE_CONTEXT_AFC9470FE8DF4FD682C297E3488583D5

#include <runtime/gameplay/gui/window.hpp>
#include <runtime/management/ecs/ecs_coordinator.hpp>
#include <runtime/management/graphics/renderer.hpp>
#include <runtime/management/scene/scene.hpp>
#include <runtime/resource/manager/asset_manager.hpp>
#include <runtime/resource/manager/project_manager.hpp>

namespace taixu {

class EngineContext {
public:
    std::unique_ptr<AbstractRenderer> _renderer{nullptr};
    std::unique_ptr<AssetManager>     _asset_manager{nullptr};
    std::unique_ptr<Scene>            _scene{nullptr};

    std::optional<Project> _opened_project{std::nullopt};
    Scene*                 _current_scene{nullptr};

    /**
     * @brief editor state
     */
    EngineState _state{EngineState::IDLEMODE};

    /**
     * @brief engine clock
     */
    Clock _clock{};

    void init() {
        _asset_manager = std::make_unique<AssetManager>();
        _scene         = std::make_unique<Scene>();
        _clock.reset();
    }
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_ENGINE_CONTEXT_AFC9470FE8DF4FD682C297E3488583D5
