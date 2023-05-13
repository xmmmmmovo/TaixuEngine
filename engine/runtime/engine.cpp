#include "engine.hpp"

#include <magic_enum.hpp>
#include <optional>

#include "core/base/path.hpp"
#include "core/base/public_singleton.hpp"
#include "engine_args.hpp"
#include "management/ecs/components/renderable/renderable_component.hpp"
#include "management/ecs/system/system.hpp"
#include "management/ecs/core/entity_manager.hpp"
#include "management/graphics/render/render_api.hpp"
#include "management/input/input_system.hpp"
#include "management/scene/scene.hpp"
#include "management/ecs/ecs_coordinator.hpp"
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

    // TODO: remove this test code
    ////////////////////////////////////////////////////////////////////////////
    auto scene      = std::make_unique<Scene>();
    auto scene_rawp = scene.get();
    _scene_manager->addScene("MainScene", std::move(scene));
    _scene_manager->setCurrentScene("MainScene");
    _renderer->bindScene(_scene_manager->getCurrentScene());

    _window_ptr->bindScene(_scene_manager->getCurrentScene());


    ////////////////////////////////////////////////////////////////////////////

    _context_ptr->registerOnScrollFn([this](double /*xoffset*/,
                                            double yoffset) {
        if (_scene_manager->getCurrentScene() == nullptr ||
            _scene_manager->getCurrentScene()->_camera == nullptr) {
            return;
        }

        if (_context_ptr->_state == EngineState::GAMEMODE) {
            _scene_manager->getCurrentScene()->_camera->processMouseScroll(
                    yoffset);
        }
    });

    _context_ptr->registerOnCursorPosFn([this](double xpos, double ypos) {
        if (_scene_manager->getCurrentScene() == nullptr ||
            _scene_manager->getCurrentScene()->_camera == nullptr) {
            return;
        }

        if (_context_ptr->_last_mouse_pos.x == -1.0F &&
            _context_ptr->_last_mouse_pos.y == -1.0F) {
            _context_ptr->_last_mouse_pos.x = xpos;
            _context_ptr->_last_mouse_pos.y = ypos;
        }
        _context_ptr->_mouse_pos.x = xpos;
        _context_ptr->_mouse_pos.y = ypos;
        if (_context_ptr->_cam_mode) {
            _scene_manager->getCurrentScene()->_camera->processMouseMovement(
                    _context_ptr->_mouse_pos.x -
                            _context_ptr->_last_mouse_pos.x,
                    _context_ptr->_last_mouse_pos.y -
                            _context_ptr->_mouse_pos.y);
        }
        _context_ptr->_last_mouse_pos = _context_ptr->_mouse_pos;
    });

    _window_ptr->initWithEngineRuntime(this);

    _clock.reset();
}

void Engine::update() {
    _clock.update();
    _renderer->clearSurface();
    InputSystem::getInstance().processInput(_clock.getDeltaTime(),
                                            _context_ptr.get());
    _scene_manager->update();
    _renderer->update();
}

void Engine::run() {
    while (!_context_ptr->shouldClose()) {
        update();
        _window_ptr->update();
        _context_ptr->swapBuffers();
    }
}

void Engine::destroy() { this->_window_ptr->destroy(); }

IRenderer *Engine::getRenderer() const { return _renderer.get(); }

Status Engine::loadProject(const std::string_view &path) {
    spdlog::info("Loading project: {}", path);
    Status const status = _project_manager->openProject(path);
    if (Status::OK != status) {
        spdlog::error("Failed to load project: {}",
                      magic_enum::enum_name(status));
        return status;
    }

    _asset_manager->loadWorld(_project_manager->getCurrentPath());
    _scene_manager->getCurrentScene()->ecs_coordinator.taixuworld = std::move(_asset_manager->taixuworld);
    //initialize the first level
    _scene_manager->getCurrentScene()->ecs_coordinator.loadhelper = _asset_manager.get();
    _scene_manager->getCurrentScene()->ecs_coordinator.serialize(0);
    return Status::OK;
}

Project *Engine::getOpenedProject() const {
    return this->_project_manager->getCurrentProject();
}

}// namespace taixu