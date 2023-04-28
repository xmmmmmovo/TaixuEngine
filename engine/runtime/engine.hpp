#ifndef ENGINE_H
#define ENGINE_H

#include "core/base/macro.hpp"
#include "core/base/public_singleton.hpp"
#include "management/graphics/renderer.hpp"
#include "management/physics/physics_manager.hpp"
#include "resource/asset_manager.hpp"
#include "resource/project_manager.hpp"
#include <memory>

namespace taixu {

class Engine : public PublicSingleton<Engine> {
    friend class PublicSingleton<Engine>;

private:
    std::unique_ptr<IRenderer>      _renderer{nullptr};
    std::unique_ptr<AssetManager>   _asset_manager{nullptr};
    std::unique_ptr<ProjectManager> _project_manager{nullptr};
    std::unique_ptr<PhysicsManager> _physics_manager{nullptr};

public:
    void init();
    void update();
    void destroy();

    Status loadProject(std::string_view const &path);

    [[nodiscard]] IRenderer *getRenderer() const;

    [[nodiscard]] Project *getOpenedProject() const;
};

}// namespace taixu

#endif// ENGINE_H