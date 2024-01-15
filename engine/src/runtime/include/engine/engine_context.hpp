//
// Created by xmmmmmovo on 11/12/2023.
//

#ifndef ENGINE_SRC_RUNTIME_ENGINE_CONTEXT_AFC9470FE8DF4FD682C297E3488583D5
#define ENGINE_SRC_RUNTIME_ENGINE_CONTEXT_AFC9470FE8DF4FD682C297E3488583D5

#include "common/base/cpu_clock.hpp"
#include "engine_args.hpp"
#include <gameplay/gui/window.hpp>
#include <management/graphics/rhi/tx_scene_renderer.hpp>
#include <management/scene/scene.hpp>
#include <resource/manager/asset_manager.hpp>
#include <resource/manager/project_manager.hpp>

namespace taixu {

class EngineContext {
public:
    std::unique_ptr<AbstractSceneRenderer> renderer{nullptr};
    std::unique_ptr<AssetManager>          asset_manager{nullptr};
    std::unique_ptr<Scene>                 scene{nullptr};

    std::optional<Project> opened_project{std::nullopt};

    /**
     * @brief editor state
     */
    EngineState state{EngineState::IDLEMODE};
    EngineArgs* engine_args{&EngineArgs::getInstance()};

    void init(Window* window) {
        renderer =
                SceneRendererFactory::createProduct(engine_args->render_api());
        renderer->init(window);

        asset_manager = std::make_unique<AssetManager>();
    }

    void update(float const delta_t) {

        renderer->update(delta_t, nullptr);
        renderer->presentToWindow();
    }

    void destroy() {}
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_ENGINE_CONTEXT_AFC9470FE8DF4FD682C297E3488583D5
