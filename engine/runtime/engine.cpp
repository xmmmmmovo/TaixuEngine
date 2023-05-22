#include "engine.hpp"

#include <magic_enum.hpp>
#include <optional>

#include "core/base/macro.hpp"
#include "engine_args.hpp"
#include "management/ecs/ecs_coordinator.hpp"
#include "management/graphics/render/render_api.hpp"
#include "management/input/input_system.hpp"
#include "management/scene/scene.hpp"
#include "platform/opengl/ogl_renderer.hpp"


namespace taixu {

void Engine::loadParams(const std::vector<std::string> &args) {
    EngineArgs::getInstance().loadParams(args);
}

void Engine::init(std::unique_ptr<WindowContext> context,
                  std::unique_ptr<IWindow>       window) {
    _context_ptr = std::move(context);
    _window_ptr  = std::move(window);

    GraphicsAPI const api = EngineArgs::getInstance().api;
    switch (api) {
        case GraphicsAPI::OPENGL:
            _renderer = std::make_unique<OGLRenderer>();
            break;
        case GraphicsAPI::NONE:
            break;
    }
    _renderer->init();

    _project_manager   = std::make_unique<ProjectManager>();
    _asset_manager     = std::make_unique<AssetManager>();
    _scene_manager     = std::make_unique<SceneManager>();
    _physics_manager   = std::make_unique<PhysicsManager>();
    _animation_manager = std::make_unique<AnimationManager>();

    _renderer->set_default_texture(
            _asset_manager->loadTexture(".", "assets/texture/rgba1111.png")
                    ->texture.get());

    _physics_manager->init();

    InputSystem::getInstance().initCallbacks(_context_ptr.get());

    _window_ptr->initWithEngineRuntime(this);

    _clock.reset();
}

void Engine::update() {
    _clock.update();
    float const delta_time = _clock.getDeltaTime();

    _renderer->clearSurface();
    if (_state != EngineState::EDITORMODE) {
        _physics_manager->update();
        _animation_manager->update(delta_time);
    }
    _renderer->update(delta_time);
    if (_current_scene != nullptr) {
        _current_scene->_ecs_coordinator.update();
    }
}

void Engine::run() {
    while (!_context_ptr->shouldClose()) {
        update();
        _window_ptr->update();
        _context_ptr->swapBuffers();
    }
}

void Engine::destroy() { this->_window_ptr->destroy(); }

AbstractRenderer *Engine::getRenderer() const { return _renderer.get(); }

void Engine::fromWorld2Scene(JsonWorld *world) {
    auto scene = std::make_unique<Scene>();

    _renderer->bindScene(scene.get());
    _physics_manager->bindScene(scene.get());
    _animation_manager->bindScene(scene.get());

    _current_scene = _scene_manager->addScene(world->name, std::move(scene));
    if (world->json_levels.empty()) {
        spdlog::debug("There is no level in the project");
    }

    auto &ecs_coordinator = _current_scene->_ecs_coordinator;

    //for (auto const &levels : world->json_levels) {
    auto parent_path = world->project_file_path;
    for (auto const &level : world->json_levels) {
        for (const auto &go : level.json_game_objects) {
            auto entity = ecs_coordinator.createEntity();

            if (go.renderable_component.has_value()) {
                auto renderable = RenderableComponent();
                auto model      = _asset_manager->loadModel(
                        parent_path, go.renderable_component.value().obj_path);

                if (model->gpu_data == std::nullopt) {
                    transferCPUModelToGPU(model);
                }

                renderable.model    = model;
                renderable.visiable = go.renderable_component.value().visiable;
                ecs_coordinator.addComponent(
                        entity, std::forward<RenderableComponent>(renderable));
            }

            if (go.transform_component.has_value()) {

                auto trans = TransformComponent(
                        go.transform_component.value().position.vec3,
                        go.transform_component.value().scale.vec3,
                        go.transform_component.value().rotation.quat);
                trans.makeTransformMatrix();
                ecs_coordinator.addComponent(
                        entity, std::forward<TransformComponent>(trans));

                if (go.RigidBodyComponent.has_value()) {
                    if (go.RigidBodyComponent.value().shapeType !=
                        RigidBodyShapeType::INVALID) {
                        auto rigid_body = RigidBodyComponent();
                        rigid_body.init(
                                go.RigidBodyComponent.value().shapeType,
                                go.RigidBodyComponent.value().motionType,
                                trans.translate(),
                                go.RigidBodyComponent.value()
                                        .rigid_body_scale.vec3,
                                entity, _physics_manager->_physics_scene);
                        ecs_coordinator.addComponent(
                                entity,
                                std::forward<RigidBodyComponent>(rigid_body));
                    }
                }
            }

            if (go.light_component.has_value()) {
                auto light_component        = LightComponent();
                light_component.light_color = glm::vec4(
                        go.light_component.value().light_color.vec3, 1.0f);
                light_component.type = go.light_component.value().light_type;

                ecs_coordinator.addComponent(
                        entity, std::forward<LightComponent>(light_component));
            }

            GameObject game_object{};
            game_object.set_name(go.name);
            game_object.set_entity(entity);
            _current_scene->game_objs().push_back(std::move(game_object));
        }
    }

    auto const &global_render = world->global_json.render_global_json;

    _current_scene->_skybox_texture = std::make_unique<OGLTextureCube>(
            (world->project_file_path / global_render.posx).string(),
            (world->project_file_path / global_render.negx).string(),
            (world->project_file_path / global_render.posy).string(),
            (world->project_file_path / global_render.negy).string(),
            (world->project_file_path / global_render.posz).string(),
            (world->project_file_path / global_render.negz).string());

    //auto fbx1 = _asset_manager->loadFBX(parent_path, "assets/fbx/phroah_character_rig.fbx");
    //    auto fbx2 = _asset_manager->loadFBX(parent_path,
    //                                        "assets/fbx/dancing_vampire.dae");

    //    //fbx2->model = fbx1->model;
    //    auto vampire_entity = _ecs_coordinator.createEntity();
    //    auto skeleton       = SkeletonComponent();
    //    skeleton.fbx        = fbx2;
    //
    //    skeleton.m_CurrentTime = 0.0;
    //    skeleton.m_FinalBoneMatrices.reserve(100);
    //    for (int i = 0; i < 100; i++)
    //        skeleton.m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
    //
    //    if (skeleton.fbx->model->gpu_data == std::nullopt) {
    //        transferCPUModelToGPU(skeleton.fbx->model);
    //    }
    //
    //    auto trans = TransformComponent(glm::vec3(0, 0, 0), glm::vec3(3, 3, 3),
    //                                    glm::vec3(0, 0, 0));
    //
    //    _ecs_coordinator.addComponent(vampire_entity,
    //                                  std::forward<TransformComponent>(trans));
    //
    //    _ecs_coordinator.addComponent(vampire_entity,
    //                                  std::forward<SkeletonComponent>(skeleton));
}

Status Engine::loadProject(const std::string_view &path) {
    spdlog::info("Loading project: {}", path);
    Status const status = _project_manager->openProject(path);
    if (Status::OK != status) {
        spdlog::error("Failed to load project: {}",
                      magic_enum::enum_name(status));
        return status;
    }

    auto world = _asset_manager->loadWorld(_project_manager->getCurrentPath());

    if (world == nullptr) { return Status::NO_SUCH_FILE_FAILED; }

    fromWorld2Scene(world);

    return Status::OK;
}

Project *Engine::getOpenedProject() const {
    return this->_project_manager->getCurrentProject();
}

Scene *Engine::getScene() const { return _current_scene; }

EngineState const &Engine::getState() const { return _state; }

ECSCoordinator *Engine::getECSCoordinator() const {
    if (_current_scene == nullptr) { return nullptr; }
    return &_current_scene->_ecs_coordinator;
}

}// namespace taixu