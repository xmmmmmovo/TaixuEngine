//
// Created by xmmmmmovo on 2023/5/2.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP

#include "gameplay/player/camera/euler_camera.hpp"
#include "management/ecs/components/Light/light_component.hpp"
#include "management/ecs/components/camera/camera_component.hpp"
#include "management/ecs/components/renderable/renderable_component.hpp"
#include "management/ecs/components/rigid_body/rigid_body_component.hpp"
#include "management/ecs/components/transform/transform_component.hpp"
<<<<<<< HEAD
#include "management/ecs/components/Light/light_component.hpp"
#include "management/ecs/components/animation/skeleton_component.hpp"
=======
>>>>>>> 61c6e611c26f0bfecf0822e9b51144ed54124d4f
#include "management/ecs/core/ecs_types.hpp"
#include "management/ecs/ecs_coordinator.hpp"
#include "management/ecs/object/game_object.hpp"
#include "management/graphics/render/texture_cube.hpp"
#include "management/input/input_system.hpp"

#include "platform/opengl/ogl_shader.hpp"

#include "management/graphics/frontend/skybox.hpp"
#include "management/graphics/render/texture_2d.hpp"
#include "platform/opengl/ogl_texture2d.hpp"
#include "platform/opengl/ogl_texture_cube.hpp"
#include "resource/manager/asset_manager.hpp"

#include "management/physics/physics_manager.hpp"

#include "skybox_frag.h"
#include "skybox_vert.h"

#include "frag_frag.h"
#include "vert_vert.h"

#include "skeleton_frag.h"
#include "skeleton_vert.h"
#include <memory>

namespace taixu {
class PhysicsManger;
class PhysicsScene;
class Scene {
private:
    using go_vec_t = std::vector<GameObject>;

    PROTOTYPE_ONLY_GETTER(private, go_vec_t, game_objs)

public:
    ECSCoordinator _ecs_coordinator{};

    Skybox                        _skybox{};
    std::unique_ptr<ITextureCube> _skybox_texture{nullptr};

    std::vector<std::unique_ptr<ITexture2D>> _textures2D;

    std::unique_ptr<EulerCamera> _camera{
            std::make_unique<EulerCamera>(glm::vec3(0.0f, 2.0f, 10.5f))};
    AssetManager               *_asset_manager{nullptr};
    std::weak_ptr<PhysicsScene> _physics_scene;

    explicit Scene() {
        _ecs_coordinator.init();
        _ecs_coordinator.registerComponent<RenderableComponent>();
        _ecs_coordinator.registerComponent<TransformComponent>();
        _ecs_coordinator.registerComponent<LightComponent>();
        _ecs_coordinator.registerComponent<RigidBodyComponent>();
        _ecs_coordinator.registerComponent<SkeletonComponent>();

    }

    void fromWorld(JsonWorld *world, int levelIndex) {
        if (world->json_levels.empty()) {
            spdlog::debug("There is no level in the project");
        }

        //for (auto const &levels : world->json_levels) {
        auto parent_path   = world->project_file_path;
        auto current_level = world->json_levels[levelIndex];
        for (const auto &go : current_level.json_game_objects) {
            auto entity = _ecs_coordinator.createEntity();

            auto renderable = RenderableComponent();
            auto model      = _asset_manager->loadModel(parent_path,
                                                        go.MeshComponent.obj_path);

            if (model->gpu_data == std::nullopt) {
                transferCPUModelToGPU(model);
            }

            renderable.model    = model;
            renderable.visiable = go.MeshComponent.visiable;
            _ecs_coordinator.addComponent(
                    entity, std::forward<RenderableComponent>(renderable));

            auto trans =
                    TransformComponent(go.TransformComponent.position.vec3,
                                       go.TransformComponent.scale.vec3,
                                       go.TransformComponent.rotation.vec3);
            trans.makeTransformMatrix();

            if (go.RigidBodyComponent.shapeType !=
                RigidBodyShapeType::INVALID) {
                auto rigid_body = RigidBodyComponent();
                rigid_body.init(go.RigidBodyComponent.shapeType,
                                go.RigidBodyComponent.motionType,
                                trans.translate(),
                                go.RigidBodyComponent.rigid_body_scale.vec3,
                                entity, _physics_scene);
                _ecs_coordinator.addComponent(
                        entity, std::forward<RigidBodyComponent>(rigid_body));
            }

            _ecs_coordinator.addComponent(
                    entity, std::forward<TransformComponent>(trans));

            GameObject game_object{};
            game_object.set_name(go.name);
            game_object.set_entity(entity);

            _game_objs.push_back(game_object);
        }
        //lights
        for (auto light : current_level.json_lights) {
            auto light_entity = _ecs_coordinator.createEntity();

            auto trans =
                    TransformComponent(light.TransformComponent.position.vec3,
                                       light.TransformComponent.scale.vec3,
                                       light.TransformComponent.rotation.vec3);

            _ecs_coordinator.addComponent(
                    light_entity, std::forward<TransformComponent>(trans));

            auto light_component = LightComponent();
            light_component.light_color =
                    glm::vec4(light.light_color.vec3, 1.0f);
            light_component.type = light.light_type;

            _ecs_coordinator.addComponent(
                    light_entity,
                    std::forward<LightComponent>(light_component));
        }

        auto const &global_render = world->global_json.render_global_json;

        _skybox_texture = std::make_unique<OGLTextureCube>(
                (world->project_file_path / global_render.posx).string(),
                (world->project_file_path / global_render.negx).string(),
                (world->project_file_path / global_render.posy).string(),
                (world->project_file_path / global_render.negy).string(),
                (world->project_file_path / global_render.posz).string(),
                (world->project_file_path / global_render.negz).string());

        for (auto const &tx : world->global_json.json_textures) {
            auto tempview   = world->project_file_path / tx.texture_path;
            auto textures2D = std::make_unique<OGLTexture2D>(
                    tempview.string(), GL_LINEAR, GL_REPEAT);
            _textures2D.push_back(std::move(textures2D));
        }
        /////////////////////////////////////////
<<<<<<< HEAD
        std::swap(_textures2D[0],_textures2D[1]);
        /////////////////////////////////////////    
        auto fbx1 = _asset_manager->loadFBX(parent_path, "assets/fbx/phroah_character_rig.fbx");
        auto fbx2 = _asset_manager->loadFBX(parent_path, "assets/fbx/dancing_vampire.dae");
        
        fbx2->model = fbx1->model;
        auto vampire_entity = _ecs_coordinator.createEntity();
        auto skeleton = SkeletonComponent();
        skeleton.fbx = fbx2;

        skeleton.m_CurrentTime = 0.0;
        skeleton.m_FinalBoneMatrices.reserve(100);
		for (int i = 0; i < 100; i++)
			skeleton.m_FinalBoneMatrices.push_back(glm::mat4(1.0f));

        if (skeleton.fbx->model->gpu_data == std::nullopt) {
                    transferCPUModelToGPU(skeleton.fbx->model);
                }
        
        auto trans =
                        TransformComponent(glm::vec3(0,0,0),
                                           glm::vec3(3,3,3),
                                           glm::vec3(0,0,0));
        
        _ecs_coordinator.addComponent(
                        vampire_entity, std::forward<TransformComponent>(trans));
                        
        _ecs_coordinator.addComponent(
                vampire_entity, std::forward<SkeletonComponent>(skeleton));
        ////////////////////////////////////////
=======
        std::swap(_textures2D[0], _textures2D[1]);
        /////////////////////////////////////////
>>>>>>> 61c6e611c26f0bfecf0822e9b51144ed54124d4f
    }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_HPP
