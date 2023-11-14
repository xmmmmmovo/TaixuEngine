#include "engine.hpp"

#include <magic_enum.hpp>
#include <optional>

#include "engine_args.hpp"
#include "resource/manager/project_manager.hpp"
#include <runtime/management/ecs/ecs_coordinator.hpp>
#include <runtime/management/input/input_system.hpp>
#include <runtime/management/scene/scene.hpp>

#include <common/base/macro.hpp>

namespace taixu {

void Engine::parseParams(const std::vector<std::string>& args) {
    EngineArgs::getInstance().loadParams(args);
}

void Engine::init() {}

void Engine::update() {
    //    _clock.update();
    //    float const delta_time = _clock.getDeltaTime();
    //
    //    _renderer->clearSurface();
    //    _renderer->update(delta_time);
    //    if (_current_scene != nullptr) {
    //        _current_scene->_ecs_coordinator.update();
    //    }
}

void Engine::destroy() {}

}// namespace taixu