#ifndef TAIXUENGINE_PHYSICS_MANAGER
#define TAIXUENGINE_PHYSICS_MANAGER

#include "core/base/hash.hpp"
#include "management/ecs/system/system.hpp"
#include "management/scene/scene.hpp"
#include "physics_scene.hpp"
#include "management/ecs/system/system.hpp"
namespace taixu {
class Scene;
class PhysicsManager {
public:
    PhysicsManager() = default;

    void init();

    void update();

    void bindScene(Scene *scene);

    std::shared_ptr<PhysicsScene> _physics_scene;
    Scene                        *_current_scene{nullptr};
    static constexpr hash64_t     PHYSICS_SYSTEM_ID = "physics_system"_hash64;
    System                       *_physics_system{nullptr};

};

}// namespace taixu


#endif /* TAIXUENGINE_PHYSICS_MANAGER */
