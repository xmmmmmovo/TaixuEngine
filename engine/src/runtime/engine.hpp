#ifndef ENGINE_H
#define ENGINE_H

#include <common/base/macro.hpp>
#include <common/base/public_singleton.hpp>

#include <filesystem>
#include <runtime/gameplay/gui/window.hpp>
#include <runtime/gameplay/gui/window_context.hpp>
#include <runtime/management/ecs/ecs_coordinator.hpp>
#include <runtime/management/graphics/renderer.hpp>
#include <runtime/management/scene/scene.hpp>
#include <runtime/management/scene/scene_manager.hpp>
#include <runtime/resource/manager/asset_manager.hpp>
#include <runtime/resource/manager/project_manager.hpp>

#include <memory>

namespace taixu {

class Engine final : public PublicSingleton<Engine> {
    friend class PublicSingleton<Engine>;

private:
    std::unique_ptr<AbstractRenderer> _renderer{nullptr};
    std::unique_ptr<AssetManager>     _asset_manager{nullptr};
    std::unique_ptr<SceneManager>     _scene_manager{nullptr};


    std::unique_ptr<WindowContext> _context_ptr{nullptr};
    std::unique_ptr<IWindow>       _window_ptr{nullptr};


    std::optional<Project> _opened_project{std::nullopt};
    Scene*                 _current_scene{nullptr};

    /**
     * @brief editor state
     */
    EngineState _state{EngineState::EDITORMODE};

    /**
     * @brief engine clock
     */
    Clock _clock{};

private:
    void update();

public:
    static void loadParams(std::vector<std::string> const& args);

    void init(std::unique_ptr<WindowContext> context,
              std::unique_ptr<IWindow>       window);

    void run();

    void destroy();

    void loadProject(std::filesystem::path const& path);

    [[nodiscard]] AbstractRenderer* getRenderer() const;

    [[nodiscard]] Project const* getOpenedProject() const;

    [[nodiscard]] Scene* getScene() const;

    [[nodiscard]] EngineState const& getState() const;

    [[nodiscard]] ECSCoordinator* getECSCoordinator() const;
};

}// namespace taixu

#endif// ENGINE_H