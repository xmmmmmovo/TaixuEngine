#include "engine.hpp"

#include <magic_enum.hpp>

namespace taixu {

Engine::Engine() {}

Engine::~Engine() {}

void Engine::init() {
    renderer = std::make_shared<Renderer>();
    renderer->initialize();

    project_manager = std::make_unique<ProjectManager>();
    asset_manager   = std::make_shared<AssetManager>();
    entity_component_system = std::make_shared<ECS>();

    entity_component_system->initialize();
    //temptory
    MeshComponent mesh;
    std::uint32_t testid = 0;
    mesh.mesh_path="mesh";
    mesh.material_path="material";
    mesh.visiable=true;
    entity_component_system->all_components[0]->addComponent(testid,mesh);
    


    // testmesh.addComponent(testid,mesh);
    // entity_component_system->addComponentType<MeshComponent>();
    //entity_component_system->components[""]=testmesh;

    int a=0;
}

void Engine::run() {}

void Engine::shutdown() {}

std::shared_ptr<Renderer> Engine::getRenderer() const { return renderer; }

Status Engine::loadProject(const std::string_view& path) {
    spdlog::info("Loading project: {}", path);
    Status status = project_manager->openProject(path);
    if (Status::OK != status) {
        spdlog::error("Failed to load project: {}",
                      magic_enum::enum_name(status));
        return status;
    }

    this->project = project_manager->getCurrentProject();
    asset_manager->loadAsset(this->project->asset_configure_path);
    return Status::OK;
}

}// namespace taixu