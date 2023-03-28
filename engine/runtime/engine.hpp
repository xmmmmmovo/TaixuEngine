#ifndef ENGINE_H
#define ENGINE_H

#include "core/base/macro.hpp"
#include "core/base/public_singleton.hpp"
#include "graphics/renderer.hpp"
#include "resource/project_manager.hpp"

namespace taixu {

class Engine : public PublicSingleton<Engine> {
    friend class PublicSingleton<Engine>;

private:
    std::shared_ptr<Renderer>       renderer{nullptr};
    std::shared_ptr<Project>        project{nullptr};
    std::shared_ptr<AssetManager>   asset_manager{nullptr};
    std::unique_ptr<ProjectManager> project_manager{nullptr};

public:
    Engine();
    ~Engine();

    void init();
    void update();
    void shutdown();

    Status loadProject(std::string_view const &path);

    [[nodiscard]] std::shared_ptr<Renderer> getRenderer() const;
};

}// namespace taixu

#endif// ENGINE_H