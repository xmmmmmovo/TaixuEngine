#include "engine.hpp"

#include <magic_enum.hpp>

#include "core/base/public_singleton.hpp"
#include "engine_args.hpp"
#include "graphics/render/render_api.hpp"
#include "gui/input_system.hpp"
#include "platform/opengl/ogl_renderer.hpp"

namespace taixu {

void Engine::init() {
    GraphicsAPI const api = EngineArgs::getInstance().api;
    switch (api) {
        case GraphicsAPI::OPENGL:
            _renderer = std::make_unique<OGLRenderer>();
            break;
        case GraphicsAPI::NONE:
            break;
    }
    _renderer->initialize();

    _project_manager = std::make_unique<ProjectManager>();
    _asset_manager   = std::make_unique<AssetManager>();
    _physics_manager = std::make_unique<PhysicsManager>();
    _physics_manager->initialize();

    _entity_component_system = std::make_unique<ECS>();
    _entity_component_system->sceneRedirection(_physics_manager->current_scene);
    _entity_component_system->initialize();
}

void Engine::update() {
    _renderer->clearSurface();
    InputSystem::getInstance().processInput();
    _entity_component_system->tick();
    _physics_manager->tick();
    _renderer->tick();
}

void Engine::shutdown() {}

IRenderer *Engine::getRenderer() const { return _renderer.get(); }

Status Engine::loadProject(const std::string_view &path) {
    spdlog::info("Loading project: {}", path);
    Status const status = _project_manager->openProject(path);
    if (Status::OK != status) {
        spdlog::error("Failed to load project: {}",
                      magic_enum::enum_name(status));
        return status;
    }

    _asset_manager->loadAsset(
            this->_project_manager->getCurrentProject()->asset_configure_path);
    return Status::OK;
}

Project *Engine::getOpenedProject() const {
    return this->_project_manager->getCurrentProject();
}

}// namespace taixu