#ifndef TAIXUENGINE_GAME_OBJECT_JSON_HPP
#define TAIXUENGINE_GAME_OBJECT_JSON_HPP

#include "mesh_json.hpp"
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
    JsonTransform         TransformComponent;
    JsonMesh              MeshComponent;
    JsonRigidBody         RigidBodyComponent;

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

            TransformComponent.to_json(t, TransformComponent);

            MeshComponent.to_json(m, MeshComponent);

            RigidBodyComponent.to_json(r, RigidBodyComponent);

            json write{{"TransformComponent", t},
                       {"MeshComponent", m},
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

        TransformComponent.from_json(components["TransformComponent"],
                                     TransformComponent);
        MeshComponent.from_json(components["MeshComponent"], MeshComponent);
        RigidBodyComponent.from_json(components["RigidBodyComponent"],
                                     RigidBodyComponent);
    }
};


}// namespace taixu
#endif /* TAIXUENGINE_GAME_OBJECT_JSON_HPP */