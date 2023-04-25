#ifndef TAIXUENGINE_ENTITY_COMPONENT_SYSTEM
#define TAIXUENGINE_ENTITY_COMPONENT_SYSTEM

//#include <unordered_map>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include "game_object.hpp"
#include "guid_genenrator.hpp"
#include "management/ecs/entity_component/entity_component.hpp"
#include "management/ecs/entity_component/mesh/mesh_component.hpp"
#include "management/ecs/entity_component/rigid_body/rigid_body_component.hpp"
#include "management/physics/physics_manager.hpp"
#include "spdlog/spdlog.h"
#include "world_manager.hpp"


namespace taixu {
enum class ComponentType { MESH_COMPONENT, TRANSFORM_COMPONENT };

class ECS {
public:
    std::weak_ptr<PhysicsScene> scene_target;
    void                        initialize();
    void sceneRedirection(std::shared_ptr<PhysicsScene> physics_scene);

    void reloadWorld(const std::filesystem::path &world_path);

    void tick(float delta_time = 0.033);

private:
    std::vector<EntityComponentMap>                  all_components;
    std::shared_ptr<WorldManager>                    taixu_world;
    std::vector<std::unique_ptr<TransformComponent>> global_transform;
};

}// namespace taixu

#endif /* TAIXUENGINE_ENTITY_COMPONENT_SYSTEM */
