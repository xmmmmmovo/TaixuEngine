#include "engine.hpp"

#include <magic_enum.hpp>
#include <optional>

#include "core/base/macro.hpp"
#include "core/base/path.hpp"
#include "core/base/public_singleton.hpp"
#include "engine_args.hpp"
#include "management/ecs/components/renderable/renderable_component.hpp"
#include "management/ecs/core/entity_manager.hpp"
#include "management/ecs/ecs_coordinator.hpp"
#include "management/ecs/object/game_object.hpp"
#include "management/ecs/system/system.hpp"
#include "management/graphics/render/render_api.hpp"
#include "management/input/input_system.hpp"
#include "management/scene/scene.hpp"
#include "platform/opengl/ogl_renderer.hpp"
#include "resource/raw_data/model.hpp"
 

namespace taixu {

void Engine::loadParams(const std::vector<std::string> &args) {
    EngineArgs::getInstance().loadParams(args);
}

void Engine::init(std::unique_ptr<WindowContext> context,
                  std::unique_ptr<IWindow>       window) {
    _context_ptr = std::move(context);
    _window_ptr  = std::move(window);

    GraphicsAPI const api = EngineArgs::getInstance().api;
    switch (api) {
        case GraphicsAPI::OPENGL:
            _renderer = std::make_unique<OGLRenderer>();
            break;
        case GraphicsAPI::NONE:
            break;
    }
    _renderer->init();

    _project_manager = std::make_unique<ProjectManager>();
    _asset_manager   = std::make_unique<AssetManager>();
    _scene_manager   = std::make_unique<SceneManager>();
    _physics_manager = std::make_unique<PhysicsManager>();
    _animation_manager = std::make_unique<AnimationManager>();

    _physics_manager->init();

    InputSystem::getInstance().initCallbacks(_context_ptr.get());

    _window_ptr->initWithEngineRuntime(this);

    _clock.reset();
}

void Engine::update() {
    _clock.update();
    float const delta_time = _clock.getDeltaTime();

    _renderer->clearSurface();
    if (_state != EngineState::EDITORMODE) { _physics_manager->update(); }
    _renderer->update(delta_time);
    if (_current_scene != nullptr) {
        _current_scene->_ecs_coordinator.update();
    }
    // _physics_manager->update();
    // _animation_manager->update(_clock.getDeltaTime());
    // _renderer->update(_clock.getDeltaTime());

}

void Engine::run() {
    while (!_context_ptr->shouldClose()) {
        update();
        _window_ptr->update();
        _context_ptr->swapBuffers();
    }
}

void Engine::destroy() { this->_window_ptr->destroy(); }

AbstractRenderer *Engine::getRenderer() const { return _renderer.get(); }

Status Engine::loadProject(const std::string_view &path) {
    spdlog::info("Loading project: {}", path);
    Status const status = _project_manager->openProject(path);
    if (Status::OK != status) {
        spdlog::error("Failed to load project: {}",
                      magic_enum::enum_name(status));
        return status;
    }

    _asset_manager->writeWorld(_project_manager->getCurrentPath());
    _asset_manager->loadWorld(_project_manager->getCurrentPath());

    auto scene = std::make_unique<Scene>();
    _renderer->bindScene(scene.get());
    _physics_manager->bindScene(scene.get());
    _animation_manager->bindScene(scene.get());

    scene->_physics_scene = _physics_manager->_physics_scene;

    _scene_manager->addScene("MainScene", std::move(scene));
    _current_scene = _scene_manager->getScene("MainScene");

    _current_scene->_asset_manager = _asset_manager.get();
    _current_scene->fromWorld(_asset_manager->taixuworld.get(), 0);

    return Status::OK;
}

Project *Engine::getOpenedProject() const {
    return this->_project_manager->getCurrentProject();
}

Scene *Engine::getScene() const { return _current_scene; }

EngineState const &Engine::getState() const { return _state; }

ECSCoordinator *Engine::getECSCoordinator() const {
    if (_current_scene == nullptr) { return nullptr; }
    return &_current_scene->_ecs_coordinator;
}

}// namespace taixu