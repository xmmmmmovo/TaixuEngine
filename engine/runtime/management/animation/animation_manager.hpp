#ifndef TAIXUENGINE_ANIMATION_MANAGRR_HPP
#define TAIXUENGINE_ANIMATION_MANAGRR_HPP


#include "core/base/hash.hpp"
#include "management/ecs/system/system.hpp"
#include "management/scene/scene.hpp"
#include "management/ecs/components/animation/skeleton_component.hpp"
namespace taixu
{
class AnimationManager
{
public:
    void update(float deltatime);

    void bindScene(Scene *scene);

    Scene                        *_current_scene{nullptr};
    static constexpr hash64_t     ANIMATION_SYSTEM_ID = "animation_system"_hash64;
    System                       *_animation_system{nullptr};
};


}
#endif /* TAIXUENGINE_ANIMATION_MANAGRR_HPP */
