#ifndef TAIXUENGINE_ENTITY_COMPONENT_SYSTEM
#define TAIXUENGINE_ENTITY_COMPONENT_SYSTEM

//#include <unordered_map>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include "game_object.hpp"
#include "resource/ecs/entity_component/entity_component.hpp"
#include "resource/ecs/entity_component/mesh/mesh_component.hpp"
#include "resource/guid_genenrator.hpp"
#include "spdlog/spdlog.h"
#include "world_manager.hpp"

namespace taixu
{


class ECS
{
public:
    ECS(){};
    ~ECS(){};
    
    void initialize();

    void reloadWorld(const std::filesystem::path &world_path); 

    void tick(float delta_time=0.033);

private:
    std::vector<std::shared_ptr<EntityComponentMap>> all_components;
    std::shared_ptr<WorldManager> taixu_world;
};

}

#endif /* TAIXUENGINE_ENTITY_COMPONENT_SYSTEM */
