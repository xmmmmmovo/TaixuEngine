#include "entity_component_system.hpp"


namespace taixu {
void ECS::initialize() 
{
    taixu_world=std::make_shared<WorldManager>();
    taixu_world->initialize();
    
    std::shared_ptr<EntityComponentMap> mesh_component_map=std::make_shared<EntityComponentMap>();
    all_components.push_back(mesh_component_map);

    //temporary read obj.json

    auto &current_GO = taixu_world->current_level->GOs[0];
    //add
    auto mesh=std::make_shared<MeshComponent>(true,"assets/model/cube.obj","material");
    mesh->loadModelData();
    mesh->data_target=data_target;
    
    all_components[0]->addComponent(current_GO.get_id(),mesh);

    auto testmesh = all_components[0]->getComponent(current_GO.get_id());

    // //modify
    // auto newmesh=std::make_shared<MeshComponent>(true,"new","new");
    // all_components[0]->addComponent(current_GO.get_id(),newmesh.get());
    //int a=0;
}

void ECS::dataRedirection(
        std::shared_ptr<Render_Context> render_context) 
{
    data_target=render_context;
    //int a=0;
}

void ECS::reloadWorld(const std::filesystem::path & world_path)
{

}

void ECS::tick(float delta_time) 
{
for(auto map:all_components)
{
    for(auto cpnt:map->map)
    {
        cpnt.second->tick();
    }
}

}
}


