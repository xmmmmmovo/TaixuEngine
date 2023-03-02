#include "engine.hpp"

namespace taixu {

Engine::Engine() {}

Engine::~Engine() {}

void Engine::init() {
    renderer = std::make_shared<Renderer>();
    renderer->initialize();

    project_manager = std::make_unique<ProjectManager>();
    asset_manager   = std::make_shared<AssetManager>();
}

void Engine::run() {}

void Engine::shutdown() {}

std::shared_ptr<Renderer> Engine::getRenderer() const { return renderer; }

Status Engine::loadProject(const std::string_view& path) {
    spdlog::info("Loading project: {}", path);
    project_manager->openProject(path);
    return Status::OK;
}

}// namespace taixu