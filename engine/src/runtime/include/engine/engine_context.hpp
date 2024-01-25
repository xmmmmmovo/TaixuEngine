//
// Created by xmmmmmovo on 11/12/2023.
//

#ifndef ENGINE_SRC_RUNTIME_ENGINE_CONTEXT_AFC9470FE8DF4FD682C297E3488583D5
#define ENGINE_SRC_RUNTIME_ENGINE_CONTEXT_AFC9470FE8DF4FD682C297E3488583D5

#include "engine/engine_args.hpp"

namespace taixu {

class AssetManager;
class AbstractSceneRenderer;
class Scene;
struct Project;

class EngineArgs;
class Window;

class EngineContext {
public:
    std::shared_ptr<AbstractSceneRenderer> renderer{nullptr};
    std::shared_ptr<AssetManager>          asset_manager{nullptr};
    std::shared_ptr<Scene>                 scene{nullptr};

    std::shared_ptr<Project> opened_project{nullptr};

    /**
     * @brief editor state
     */
    EngineState state{EngineState::IDLEMODE};
    EngineArgs  engine_args{};

    void init(Window* window);

    void destroy() const;
};

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_ENGINE_CONTEXT_AFC9470FE8DF4FD682C297E3488583D5
