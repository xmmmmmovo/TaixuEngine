#ifndef TAIXUENGINE_GAME_OBJECT_JSON_HPP
#define TAIXUENGINE_GAME_OBJECT_JSON_HPP

#include "animation_json.hpp"
#include "renderable_json.hpp"
#include "resource/json/json_type/light_json.hpp"
#include "rigid_body_json.hpp"
#include "transform_json.hpp"

#include <fstream>

namespace taixu {

using json = nlohmann::json;

class JsonGO {
public:
    std::string           name;
    std::string           GO_path{"INVALID"};
    std::filesystem::path project_file_path{"INVALID"};

    std::optional<JsonTransform>  transform_component;
    std::optional<JsonRenderable> renderable_component;
    std::optional<JsonRigidBody>  RigidBodyComponent;
    std::optional<JsonLight>      light_component;

    void to_json(nlohmann::json &j, const JsonGO &go) {
        j = nlohmann::json{{"name", go.name}, {"GO_path", go.GO_path}};
    }

    void from_json(const nlohmann::json &j, JsonGO &go) {
        j.at("name").get_to(go.name);
        j.at("GO_path").get_to(go.GO_path);
    }

    void serialize() {
        if (GO_path != "INVALID") {
            std::ofstream o(project_file_path / GO_path);

            json t, m, r;

            transform_component.value().to_json(t, transform_component.value());

            renderable_component.value().to_json(m,
                                                 renderable_component.value());

            RigidBodyComponent.value().to_json(r, RigidBodyComponent.value());

            json write{{"transform_component", t},
                       {"renderable_component", m},
                       {"RigidBodyComponent", r}};
            json GOs{{"Components", write}};
            o << std::setw(4) << GOs;
            o.close();
        }
    }

    void deserialize() {
        std::ifstream f(project_file_path / GO_path);
        if (!f.is_open()) {
            spdlog::debug("Unable to load GO's configure file");
        }

        json data       = json::parse(f);
        json components = data["Components"];

        if (components["TransformComponent"].is_null()) {
            transform_component = std::nullopt;
        } else {
            auto json_trans = JsonTransform();
            json_trans.from_json(components["TransformComponent"], json_trans);
            transform_component = json_trans;
        }

        if (components["RenderableComponent"].is_null()) {
            renderable_component = std::nullopt;
        } else {
            auto json_renderable = JsonRenderable();
            json_renderable.from_json(components["RenderableComponent"],
                                      json_renderable);
            renderable_component = json_renderable;
        }

        if (components["RigidBodyComponent"].is_null()) {
            RigidBodyComponent = std::nullopt;
        } else {
            auto json_rigidbody = JsonRigidBody();
            json_rigidbody.from_json(components["RigidBodyComponent"],
                                     json_rigidbody);
            RigidBodyComponent = json_rigidbody;
        }

        if (components["LightComponent"].is_null()) {
            light_component = std::nullopt;
        } else {
            auto json_light = JsonLight();
            json_light.from_json(components["LightComponent"], json_light);
            light_component = json_light;
        }
    }
};


}// namespace taixu
#endif /* TAIXUENGINE_GAME_OBJECT_JSON_HPP */