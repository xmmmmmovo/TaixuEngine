#ifndef ENGINE_H
#define ENGINE_H

#include "core/base/macro.hpp"
#include "core/base/public_singleton.hpp"
#include "gameplay/gui/window.hpp"
#include "gameplay/gui/window_context.hpp"
#include "management/ecs/ecs_coordinator.hpp"
#include "management/graphics/renderer.hpp"
#include "management/physics/physics_manager.hpp"
#include "management/scene/scene.hpp"
#include "management/scene/scene_manager.hpp"
#include "resource/manager/asset_manager.hpp"
#include "resource/manager/project_manager.hpp"

#include <memory>

namespace taixu {

class Engine final : public PublicSingleton<Engine> {
    friend class PublicSingleton<Engine>;

private:
    std::unique_ptr<IRenderer>      _renderer{nullptr};
    std::unique_ptr<AssetManager>   _asset_manager{nullptr};
    std::unique_ptr<ProjectManager> _project_manager{nullptr};
    std::unique_ptr<SceneManager>   _scene_manager{nullptr};

    std::unique_ptr<WindowContext> _context_ptr{nullptr};
    std::unique_ptr<IWindow>       _window_ptr{nullptr};

    Scene                     *_current_scene{nullptr};
    std::unique_ptr<JsonWorld> taixuworld;

    Clock _clock{};

    void update();

public:
    void loadParams(std::vector<std::string> const &args);

    void init(std::unique_ptr<WindowContext> context,
              std::unique_ptr<IWindow>       window);

    void run();

    void destroy();

    Status loadProject(std::string_view const &path);

    [[nodiscard]] IRenderer *getRenderer() const;

    [[nodiscard]] Project *getOpenedProject() const;

    std::vector<GameObject> const &getGameObjects();
};

}// namespace taixu

#endif// ENGINE_H