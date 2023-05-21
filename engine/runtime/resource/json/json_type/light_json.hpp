#ifndef TAIXUENGINE_LIGHT_JSON_HPP
#define TAIXUENGINE_LIGHT_JSON_HPP

#include "management/ecs/components/light/light_source_type.hpp"
#include "transform_json.hpp"

namespace taixu {

class JsonLight {
public:
    Vec3            light_color;
    LightSourseType light_type;

    void to_json(nlohmann::json &j, JsonLight &light) {
        nlohmann::json c, t;
        light.light_color.to_json(c, light.light_color);
        t = nlohmann::json{{"LightSourseType", light_type}};
        j = nlohmann::json{{"LightColor", c}, {"LightType", t}};
    }

    void from_json(const nlohmann::json &j, JsonLight &light) {
        light.light_color.from_json(j["LightColor"], light.light_color);
        light.light_type = j["LightSourseType"].get<LightSourseType>();
    }
};
}// namespace taixu

#endif /* TAIXUENGINE_LIGHT_JSON_HPP */
