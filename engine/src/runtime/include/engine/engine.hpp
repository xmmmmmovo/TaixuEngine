
#pragma once

#include "common/base/cpu_clock.hpp"
#include "common/designs/noncopyable.hpp"
#include "engine/engine_args.hpp"
#include "management/scene/tx_scene_renderer.hpp"
#include "resource/json_data/project_json.hpp"

#include <string>

namespace taixu {

class AssetManager;
class Scene;
class EngineArgs;
class Window;

class Engine final : public Noncopyable {
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
    std::unique_ptr<Project> _opened_project{nullptr};

    /**
     * @brief hold window from init function
     */
    Window* _window{nullptr};

public:
    /**
     * 渲染器
     */
    std::shared_ptr<TXSceneRenderer> renderer{nullptr};
    /**
     * 资源管理器
     */
    std::shared_ptr<AssetManager>    asset_manager{nullptr};
    /**
     * 打开场景
     */
    std::shared_ptr<Scene>           scene{nullptr};

public:
    /**
     * 在最开始传递参数化表的初始化，用于初始化比如Logger之类的
     * @param args 初始化参数表
     */
    void initRuntime(std::vector<std::string> const& args);
    /**
     * 用于初始化渲染器和资源管理器等
     * @param window
     */
    void initWithWindow(Window* window);

    /**
     * @brief This function only need call once before main loop
     */
    void beforeStart();
    void update();
    void destroy() const;

    EngineArgs const& getArgs();

    void changeEngineState(EnumEngineState state);

    bool                         loadProject(std::filesystem::path const& path);
    [[nodiscard]] Project const* getOpenedProject() const;
};

extern Engine g_engine;

}// namespace taixu
