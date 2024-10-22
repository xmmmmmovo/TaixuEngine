#include "taixu/engine/engine.hpp"

#include "taixu/common/log/logger.hpp"

#include "management/scene/scene.hpp"
#include "management/scene/tx_scene_renderer.hpp"
#include "resource/helper/project_helper.hpp"
#include "resource/manager/asset_manager.hpp"


namespace taixu {

Engine g_engine;// NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

struct EnginePrivate {
    /**
     * @brief Engine状态
     */
    EngineState _state{EngineState::IDLEMODE};

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
    std::unique_ptr<TXSceneRenderer> renderer{nullptr};
    /**
     * 资源管理器
     */
    std::unique_ptr<AssetManager>    asset_manager{nullptr};
};

Engine::Engine() {
    _p = std::make_unique<EnginePrivate>();
}

void Engine::initRuntime(std::vector<std::string> const& args) {
    Logger::init();
    INFO_LOG("Logger inited, start init engine");
    _engine_args.initWithArgs(args);
}

void Engine::initWithWindow(Window* window) {
    _p->_window = window;

    _p->renderer = std::make_unique<TXSceneRenderer>();
    _p->renderer->init(window);

    _p->asset_manager = std::make_unique<AssetManager>();
}

void Engine::beforeStart() {
    _clock.reset();
}

void Engine::update() {
    _clock.update();
    float const delta_time = _clock.getDeltaTime();
    _p->renderer->update(delta_time, nullptr);
}

void Engine::destroy() const {
    _p->renderer->destroy();
    Logger::destroy();
}

EngineArgs const& Engine::getArgs() {
    return _engine_args;
}

void Engine::changeEngineState(const EngineState state) {
    _p->_state = state;
}

bool Engine::loadProject(std::filesystem::path const& path) {
    _p->_opened_project = openProject(path);
    if (_p->_opened_project == nullptr) {
        INFO_LOG("Cannot load project from path: {}", path.generic_string());
        return false;
    }
    return true;
}

Project const* Engine::getOpenedProject() const {
    return _p->_opened_project.get();
}

void Engine::enableImgui(std::function<void()>&& update_func) {
    _p->renderer->enableImgui(std::forward<std::function<void()>>(update_func));
}

EngineArgs const& Engine::getEngineArgs() const {
    return _engine_args;
}

}// namespace taixu
