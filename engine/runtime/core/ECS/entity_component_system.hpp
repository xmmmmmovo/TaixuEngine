#ifndef ENTITY_COMPONENT_SYSTEM
#define ENTITY_COMPONENT_SYSTEM

//#include <unordered_map>
#include <typeinfo>
#include <string>
#include <vector>
#include <memory>

#include <spdlog/spdlog.h>

#include "game_object.hpp"
#include "entity_component/entity_component.hpp"
#include "entity_component/mesh/mesh_component.hpp"

namespace taixu
{


class ECS
{
public:
    ECS(){};
    ~ECS(){};
    
    void initialize();

    void update();

//private:
    std::vector<std::shared_ptr<EntityComponentMap>> all_components;
};

}

#endif /* ENTITY_COMPONENT_SYSTEM */
