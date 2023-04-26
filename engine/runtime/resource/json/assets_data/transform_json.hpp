#ifndef TAIXUENGINE_TRANSFORM_JSON_HPP
#define TAIXUENGINE_TRANSFORM_JSON_HPP

//#include "jsonable.hpp"
#include "resource/json/json_parser.hpp"

namespace taixu
{

class Vec3 {
public:
    glm::vec3 vec3;

    void to_json(nlohmann::json& j, const Vec3& p) {
        j = nlohmann::json{{"x", p.vec3.x}, {"y", p.vec3.y}, {"z", p.vec3.z}};
    }

    void from_json(const nlohmann::json& j, Vec3& p) {
        j.at("x").get_to(p.vec3.x);
        j.at("y").get_to(p.vec3.y);
        j.at("z").get_to(p.vec3.z);
    }
};

class JsonTransform
{
public:
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;

    void to_json(nlohmann::json& j, JsonTransform& trans) {
        nlohmann::json p,t,s;
        trans.position.to_json(p, trans.position); 
        trans.rotation.to_json(t, trans.rotation);
        trans.scale.to_json(s, trans.scale);

        j = nlohmann::json{
            {"position", p}, 
            {"rotation", t}, 
            {"scale", s}
        };
    }

    void from_json(const nlohmann::json& j, JsonTransform& trans) {
        trans.position.from_json(j["position"], trans.position);
        trans.rotation.from_json(j["rotation"], trans.rotation);
        trans.scale.from_json(j["scale"], trans.scale);
    }

};



}



#endif /* TAIXUENGINE_TRANSFORM_JSON_HPP */
