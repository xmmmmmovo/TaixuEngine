#include "engine.hpp"

#include <magic_enum.hpp>

#include "core/base/public_singleton.hpp"
#include "gui/input_system.hpp"

namespace taixu {

Engine::Engine() {}

Engine::~Engine() {}

void Engine::init() {
    _renderer = std::make_shared<Renderer>();
    _renderer->initialize();

    _project_manager         = std::make_unique<ProjectManager>();
    _asset_manager           = std::make_shared<AssetManager>();
    _entity_component_system = std::make_shared<ECS>();

    _entity_component_system->initialize();
}

void Engine::update() {
    InputSystem::getInstance().processInput();
    _renderer->tick();
}

void Engine::shutdown() {}

std::shared_ptr<Renderer> Engine::getRenderer() const { return _renderer; }

Status Engine::loadProject(const std::string_view& path) {
    spdlog::info("Loading project: {}", path);
    Status status = _project_manager->openProject(path);
    if (Status::OK != status) {
        spdlog::error("Failed to load project: {}",
                      magic_enum::enum_name(status));
        return status;
    }

    this->_project = _project_manager->getCurrentProject();
    _asset_manager->loadAsset(this->_project->asset_configure_path);
    return Status::OK;
}

}// namespace taixu