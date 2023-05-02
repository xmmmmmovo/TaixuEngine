//
// Created by xmmmmmovo on 2023/5/2.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_MANAGER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_MANAGER_HPP

#include "scene.hpp"
#include <string>
#include <unordered_map>


namespace taixu {

class SceneManager final {
private:
    std::unordered_map<std::string_view, std::unique_ptr<Scene>> _scenes;
    Scene *_now_scene{nullptr};

public:
    void addScene(std::string_view const &name, std::unique_ptr<Scene> scene);

    void removeScene(std::string_view const &name);

    Scene *getScene(std::string_view const &name);

    Scene *getCurrentScene();

    void setCurrentScene(std::string_view const &name);

    void clear();
};

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_SCENE_SCENE_MANAGER_HPP
