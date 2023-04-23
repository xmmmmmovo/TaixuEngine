#ifndef ENGINE_H
#define ENGINE_H

#include "core/base/macro.hpp"
#include "core/base/public_singleton.hpp"
#include "graphics/render/render_api.hpp"
#include "graphics/render_context.hpp"
#include "graphics/renderer.hpp"
#include "gui/window_context.hpp"
#include "physics/physics_manager.hpp"
#include "resource/ecs/entity_component_system.hpp"
#include "resource/project_manager.hpp"
#include <memory>

namespace taixu {

class Engine : public PublicSingleton<Engine> {
    friend class PublicSingleton<Engine>;

private:
    std::unique_ptr<AbstractRenderer> _renderer{nullptr};
    std::unique_ptr<AssetManager>     _asset_manager{nullptr};
    std::unique_ptr<ProjectManager>   _project_manager{nullptr};
    std::unique_ptr<ECS>              _entity_component_system{nullptr};
    std::unique_ptr<PhysicsManager>   _physics_manager{nullptr};

public:
    void init();
    void update();
    void shutdown();

    Status loadProject(std::string_view const &path);

    [[nodiscard]] AbstractRenderer *getRenderer() const;

    [[nodiscard]] Project *getOpenedProject() const;
};

}// namespace taixu

#endif// ENGINE_H