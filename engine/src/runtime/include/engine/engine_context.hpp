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

class EngineContext final {
public:
    std::shared_ptr<AbstractSceneRenderer> renderer{nullptr};
    std::shared_ptr<AssetManager>          asset_manager{nullptr};
    std::shared_ptr<Scene>                 scene{nullptr};

    std::shared_ptr<Project> opened_project{nullptr};

    /**
     * @brief editor state
     */
    EnumEngineState state{EnumEngineState::IDLEMODE};
    EngineArgs  engine_args{};

    /**
     * @brief hold window from init function
     */
    Window* window{nullptr};

    void init(std::vector<std::string> const& args, Window* window);

    void destroy() const;
};

extern EngineContext g_engine_context;

}// namespace taixu

#endif// ENGINE_SRC_RUNTIME_ENGINE_CONTEXT_AFC9470FE8DF4FD682C297E3488583D5
