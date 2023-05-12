//
// Created by xmmmmmovo on 2023/4/29.
//

#include "ecs_coordinator.hpp"

namespace taixu {

void ECSCoordinator::init() {
    _component_manager = std::make_unique<ComponentManager>();
    _entity_manager    = std::make_unique<EntityManager>();
    _event_manager     = std::make_unique<EventManager>();
    _category_manager  = std::make_unique<CategoryManager>();
}

Entity ECSCoordinator::createEntity() {
    return _entity_manager->createEntity();
}

void ECSCoordinator::destroyEntity(Entity entity) {
    _entity_manager->destroyEntity(entity);
    _component_manager->entityDestroyed(entity);
    _category_manager->entityDestroyed(entity);
}

Category *ECSCoordinator::registerCategory(CategoryIdType categoryId) {
    return _category_manager->registerCategory(categoryId);
}

void ECSCoordinator::setCategorySignature(CategoryIdType categoryId,
                                          Signature      signature) {
    _category_manager->setSignature(categoryId, signature);
}

void ECSCoordinator::addEventListener(
        EventIdType eventId, const std::function<void(Event &)> &listener) {
    _event_manager->addListener(eventId, listener);
}

void ECSCoordinator::removeEventListener(EventIdType eventId) {
    this->_event_manager->removeListener(eventId);
}

void ECSCoordinator::sendEvent(Event &event) {
    _event_manager->addEvent(event);
}

void ECSCoordinator::sendEvent(EventIdType eventId) {
    _event_manager->addEvent(eventId);
}

void ECSCoordinator::update() { this->_event_manager->processEvents(); }

void ECSCoordinator::serialize(int level_index) {
    if(taixuworld->json_levels.size()==0)
        spdlog::debug("There is no level in the project");
    
    auto currentlevel_json = taixuworld->json_levels[level_index];
    auto parent_path = loadhelper->project_file_path;
    for (auto go: currentlevel_json.json_game_objects)
    {
        auto entity = createEntity();

        auto renderable = RenderableComponent();
        auto model      = loadhelper->loadModel(
        parent_path/go.MeshComponent.obj_path);

        if (model->gpu_data == std::nullopt) { transferCPUModelToGPU(model); }

        renderable.model = model;
        renderable.visiable = go.MeshComponent.visiable;
        addComponent(
            entity, std::forward<RenderableComponent>(renderable));

        auto test_rendercomp = getComponent<RenderableComponent>(entity);
        
        auto trans = TransformComponent(
            go.TransformComponent.position.vec3,
            go.TransformComponent.scale.vec3,
            go.TransformComponent.rotation.vec3
            );
            
        trans.makeTransformMatrix();

        addComponent(
            entity, std::forward<TransformComponent>(trans));
            
        
    }
    //int a = 0;
}

void ECSCoordinator::deserialize(int level_index) {

}

}// namespace taixu
