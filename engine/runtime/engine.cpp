#include "engine.hpp"

namespace taixu {

Engine::Engine() {}

Engine::~Engine() {}

void Engine::init() {
    renderer = std::make_shared<Renderer>();
    renderer->initialize();
}

void Engine::run() {}

void Engine::shutdown() {}

std::shared_ptr<Renderer> Engine::getRenderer() const { return renderer; }

Status Engine::loadProject(const std::string_view& path) { return Status::OK; }

}// namespace taixu