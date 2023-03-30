#include "engine.hpp"

#include <magic_enum.hpp>

#include "core/base/public_singleton.hpp"
#include "gui/input_system.hpp"

namespace taixu {

void Engine::init() {
    _renderer = std::make_unique<Renderer>();
    _renderer->initialize();

    _project_manager         = std::make_unique<ProjectManager>();
    _asset_manager           = std::make_unique<AssetManager>();
    _entity_component_system = std::make_unique<ECS>();
    _entity_component_system->dataRedirection(_renderer->render_context);

    _entity_component_system->initialize();
}

void Engine::update() {
    InputSystem::getInstance().processInput();
    //_entity_component_system->tick();
    _renderer->tick();
}

void Engine::shutdown() {}

Renderer* Engine::getRenderer() const { return _renderer.get(); }

Status Engine::loadProject(const std::string_view& path) {
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

}// namespace taixu