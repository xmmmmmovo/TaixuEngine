#include "taixu/engine/engine.hpp"

#include "taixu/common/log/logger.hpp"

#include "common/base/cpu_clock.hpp"
#include "management/scene/scene.hpp"
#include "management/scene/tx_scene_renderer.hpp"
#include "resource/helper/project_helper.hpp"
#include "resource/manager/asset_manager.hpp"


namespace taixu {

Engine g_engine;// NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

struct EnginePrivate {
    /**
     * @brief engine clock
     */
    CpuClock _clock{};

    /**
     * @brief Engine状态
     */
    EngineState _state{EngineState::IDLEMODE};

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
};

void Engine::initRuntime(std::vector<std::string> const& args) {
    Logger::init();
    INFO_LOG("Logger inited, start init engine");
    _engine_args.initWithArgs(args);
}

void Engine::initWithWindow(Window* window) {
    this->_window = window;

    renderer = std::make_shared<TXSceneRenderer>();
    renderer->init(window);

    asset_manager = std::make_shared<AssetManager>();
    scene         = std::make_shared<Scene>();
}

void Engine::beforeStart() {
    _clock.reset();
}

void Engine::update() {
    _clock.update();
    float const delta_time = _clock.getDeltaTime();
    renderer->update(delta_time, nullptr);
}

void Engine::destroy() const {
    renderer->destroy();
    Logger::destroy();
}

EngineArgs const& Engine::getArgs() {
    return _engine_args;
}

void Engine::changeEngineState(const EngineState state) {
    _state = state;
}

bool Engine::loadProject(std::filesystem::path const& path) {
    _opened_project = openProject(path);
    if (_opened_project == nullptr) {
        INFO_LOG("Cannot load project from path: {}", path.generic_string());
        return false;
    }
    return true;
}

Project const* Engine::getOpenedProject() const {
    return _opened_project.get();
}

}// namespace taixu
