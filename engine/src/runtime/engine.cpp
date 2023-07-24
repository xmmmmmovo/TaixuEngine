#include "engine.hpp"

#include <magic_enum.hpp>
#include <optional>

#include "engine_args.hpp"
#include "resource/converted_data/project.hpp"
#include "resource/manager/project_manager.hpp"
#include <runtime/management/ecs/ecs_coordinator.hpp>
#include <runtime/management/graphics/render/render_api.hpp>
#include <runtime/management/input/input_system.hpp>
#include <runtime/management/scene/scene.hpp>
#include <runtime/platform/opengl/ogl_renderer.hpp>

#include <common/base/macro.hpp>

namespace taixu {

void Engine::loadParams(const std::vector<std::string>& args) {
    EngineArgs::getInstance().loadParams(args);
}

void Engine::init(std::unique_ptr<WindowContext> context,
                  std::unique_ptr<IWindow>       window) {
    _context_ptr = std::move(context);
    _window_ptr  = std::move(window);

    GraphicsAPI const api = EngineArgs::getInstance().api();
    switch (api) {
        case GraphicsAPI::OPENGL:
            _renderer = std::make_unique<OGLRenderer>();
            break;
        case GraphicsAPI::NONE:
            break;
    }
    _renderer->init();

    _asset_manager = std::make_unique<AssetManager>();
    _scene_manager = std::make_unique<SceneManager>();

    _renderer->set_default_texture(
            _asset_manager->loadTexture(".", "assets/texture/rgba1111.png")
                    ->texture.get());

    InputSystem::getInstance().initCallbacks(_context_ptr.get());

    _window_ptr->initWithEngineRuntime(this);

    _clock.reset();
}

void Engine::update() {
    _clock.update();
    float const delta_time = _clock.getDeltaTime();

    _renderer->clearSurface();
    _renderer->update(delta_time);
    if (_current_scene != nullptr) {
        _current_scene->_ecs_coordinator.update();
    }
}

void Engine::run() {
    while (!_context_ptr->shouldClose()) {
        update();
        _window_ptr->update();
        _context_ptr->swapBuffers();
    }
}

void Engine::destroy() { this->_window_ptr->destroy(); }

AbstractRenderer* Engine::getRenderer() const { return _renderer.get(); }

void Engine::loadProject(const std::filesystem::path& path) {
    spdlog::info("Loading project: {}", path.generic_string());
    std::optional<Project> tpj{std::nullopt};
    try {
        tpj = openProject(path);
    } catch (std::exception& e) {
        spdlog::error("Failed to load project: {}", e.what());
        return;
    }
    glfwSetWindowTitle(this->_context_ptr->_window,
                       fmt::format("{} - {} - {}", this->_context_ptr->_title,
                                   tpj.value().manifest.name,
                                   tpj.value().current_path.generic_string())
                               .c_str());
    this->_opened_project = std::move(tpj);
}

/**
 * @brief 获取打开的项目文件
 * @return
 */
Project const* Engine::getOpenedProject() const {
    if (this->_opened_project.has_value()) {
        return &this->_opened_project.value();
    }
    return nullptr;
}

Scene* Engine::getScene() const { return _current_scene; }

EngineState const& Engine::getState() const { return _state; }

ECSCoordinator* Engine::getECSCoordinator() const {
    if (_current_scene == nullptr) { return nullptr; }
    return &_current_scene->_ecs_coordinator;
}

}// namespace taixu