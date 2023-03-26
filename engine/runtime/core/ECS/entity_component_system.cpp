#include "entity_component_system.hpp"


void taixu::ECS::initialize() 
{
    std::shared_ptr<EntityComponentMap> mesh_component_map=std::make_shared<EntityComponentMap>();
    all_components.push_back(mesh_component_map);

}

void taixu::ECS::update() {}
