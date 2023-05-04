//
// Created by xmmmmmovo on 2023/5/2.
//

#include "scene_manager.hpp"
#include "scene.hpp"

namespace taixu {

void SceneManager::addScene(const string_view     &name,
                            std::unique_ptr<Scene> scene) {
    _scenes.emplace(name, std::move(scene));
}

void SceneManager::removeScene(std::string_view const &name) {
    _scenes.erase(name);
}

Scene *SceneManager::getScene(std::string_view const &name) {
    if (_scenes.find(name) == _scenes.end()) { return nullptr; }
    return _scenes.at(name).get();
}

void SceneManager::clear() { _scenes.clear(); }

Scene *SceneManager::getCurrentScene() { return _current_scene; }

void SceneManager::setCurrentScene(const std::string_view &name) {
    _current_scene = getScene(name);
}

void SceneManager::update() {
    if (_current_scene != nullptr) { _current_scene->ecs_coordinator.update(); }
}

}// namespace taixu
