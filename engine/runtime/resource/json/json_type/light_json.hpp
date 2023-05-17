#ifndef TAIXUENGINE_LIGHT_JSON_HPP
#define TAIXUENGINE_LIGHT_JSON_HPP
#include "transform_json.hpp"
#include "management/ecs/components/Light/light_component.hpp"
namespace taixu
{
class JsonLight
{
public:
    std::string           name;
    std::string           light_path{"INVALID"};
    std::filesystem::path project_file_path{"INVALID"};
    JsonTransform         TransformComponent;
    Vec3 light_color;
    LightSourseType light_type;

    void to_json(nlohmann::json &j, const JsonLight &l) {
        j = nlohmann::json{{"name", l.name}, {"light_path", l.light_path}};

    }

    void from_json(const nlohmann::json &j, JsonLight &l) {
        j.at("name").get_to(l.name);
        j.at("light_path").get_to(l.light_path);
    }

    void serialize() {
        if (light_path != "INVALID") {
            std::ofstream o(project_file_path / light_path);

            json t,l;

            TransformComponent.to_json(t, TransformComponent);
            light_color.to_json(l,light_color);

            json write{{"TransformComponent", t},
                       {"LightSourseType",light_type},
                       {"LightColor", l}
                       };
            
            o << std::setw(4) << write;
            o.close();
        }
    }

    void deserialize() {
        std::ifstream f(project_file_path / light_path);
        if (!f.is_open()) {
            spdlog::debug("Unable to load light's configure file");
        }

        json data       = json::parse(f);
        json trans = data["TransformComponent"];
        json color = data["LightColor"];

        TransformComponent.from_json(trans,TransformComponent);
        light_color.from_json(color,light_color);
        data.at("LightSourseType").get_to(light_type);
    }
};
}

#endif /* TAIXUENGINE_LIGHT_JSON_HPP */
