#include "engine/engine.hpp"

#include <magic_enum.hpp>
#include <optional>

#include "engine/engine_args.hpp"
#include <common/log/logger.hpp>

namespace taixu {

void Engine::init(const std::vector<std::string>& args) {
    Logger::init();
    _context.init(args);
}

void Engine::start() { _clock.reset(); }

void Engine::update() {
    _clock.update();
    float const delta_time = _clock.getDeltaTime();
    //    _renderer->clearSurface();
    //    _renderer->update(delta_time);
    //    if (_current_scene != nullptr) {
    //        _current_scene->_ecs_coordinator.update();
    //    }
}

void Engine::destroy() { Logger::destroy(); }

}// namespace taixu