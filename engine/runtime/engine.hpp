#ifndef ENGINE_H
#define ENGINE_H

#include "core/base/macro.hpp"
#include "core/base/public_singleton.hpp"
#include "graphics/renderer.hpp"
#include "resource/ecs/entity_component_system.hpp"
#include "resource/project_manager.hpp"
#include "resource/ecs/entity_component_system.hpp"


namespace taixu {

class Engine : public PublicSingleton<Engine> {
    friend class PublicSingleton<Engine>;

private:
    std::unique_ptr<Renderer>       _renderer{nullptr};
    std::unique_ptr<AssetManager>   _asset_manager{nullptr};
    std::unique_ptr<ProjectManager> _project_manager{nullptr};
    std::unique_ptr<ECS>            _entity_component_system{nullptr};

public:
    void init();
    void update();
    void shutdown();

    Status loadProject(std::string_view const& path);

    [[nodiscard]] Renderer* getRenderer() const;
};

}// namespace taixu

#endif// ENGINE_H