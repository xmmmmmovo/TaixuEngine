
#pragma once

#include "common/base/cpu_clock.hpp"
#include "common/designs/noncopyable.hpp"
#include "engine/engine_args.hpp"
#include "management/scene/tx_scene_renderer.hpp"

#include <string>

namespace taixu {

class AssetManager;
class Scene;
class EngineArgs;
class Window;
struct Project;

class Engine final : private Noncopyable {
private:
    /**
     * @brief engine clock
     */
    CpuClock _clock{};

    /**
     * @brief Engine状态
     */
    EnumEngineState _state{EnumEngineState::IDLEMODE};

    /**
     * 保存engine的参数
     */
    EngineArgs _engine_args{};

    /**
     * 已经打开的项目，如果没有就是null
     */
    std::shared_ptr<Project> _opened_project{nullptr};

    /**
     * @brief hold window from init function
     */
    Window* _window{nullptr};

public:
    std::shared_ptr<AbstractSceneRenderer> renderer{nullptr};
    std::shared_ptr<AssetManager>          asset_manager{nullptr};
    std::shared_ptr<Scene>                 scene{nullptr};

public:
    void initRuntime(std::vector<std::string> const& args);
    void initWithWindow(Window* window);

    /**
     * @brief This function only need call once before main loop
     */
    void beforeStart();
    void update();
    void destroy() const;

    EngineArgs const& getArgs();

    void changeEngineState(EnumEngineState state);

    bool loadProject(std::filesystem::path const& path);
    std::shared_ptr<const Project> const& getOpenedProject();
};

extern Engine g_engine;

}// namespace taixu
