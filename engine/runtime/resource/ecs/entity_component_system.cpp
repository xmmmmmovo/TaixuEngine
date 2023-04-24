#include "entity_component_system.hpp"


namespace taixu {
void ECS::initialize() {
    taixu_world = std::make_shared<WorldManager>();
    taixu_world->initialize();

    //Due to the mesh component need to transfer data to renderer
    //So its order of tick is at the end

    EntityComponentMap mesh_component_map;
    EntityComponentMap rigid_body_component_map;

    //tick order

    all_components.push_back(rigid_body_component_map);//0
    all_components.push_back(mesh_component_map);      //1

    //temporary read obj.json
}

void ECS::sceneRedirection(std::shared_ptr<PhysicsScene> physics_scene) {
    scene_target = physics_scene;
}

void ECS::reloadWorld(const std::filesystem::path &world_path) {}

void ECS::tick(float delta_time) {
    for (auto map : all_components) {
        for (auto &cpnt : map.map) { cpnt->tick(); }
    }
}
}// namespace taixu
