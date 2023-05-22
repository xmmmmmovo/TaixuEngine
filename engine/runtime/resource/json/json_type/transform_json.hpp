#ifndef TAIXUENGINE_TRANSFORM_JSON_HPP
#define TAIXUENGINE_TRANSFORM_JSON_HPP

#include <glm/vec3.hpp>
#include <nlohmann/json.hpp>

namespace taixu {

class Vec3 {
public:
    glm::vec3 vec3;

    void to_json(nlohmann::json &j, const Vec3 &p) {
        j = nlohmann::json{{"x", p.vec3.x}, {"y", p.vec3.y}, {"z", p.vec3.z}};
    }

    void from_json(const nlohmann::json &j, Vec3 &p) {
        j.at("x").get_to(p.vec3.x);
        j.at("y").get_to(p.vec3.y);
        j.at("z").get_to(p.vec3.z);
    }
};

class Quat {
public:
    glm::quat quat;

    void to_json(nlohmann::json &j, const Quat &q) {
        j = nlohmann::json{{"x", q.quat.x},
                           {"y", q.quat.y},
                           {"z", q.quat.z},
                           {"w", q.quat.w}};
    }

    void from_json(const nlohmann::json &j, Quat &q) {
        j.at("x").get_to(q.quat.x);
        j.at("y").get_to(q.quat.x);
        j.at("z").get_to(q.quat.x);
        j.at("w").get_to(q.quat.x);
    }
};

class JsonTransform {
public:
    Vec3 position;
    Quat rotation;
    Vec3 scale;

    void to_json(nlohmann::json &j, JsonTransform &trans) {
        nlohmann::json p, t, s;
        trans.position.to_json(p, trans.position);
        trans.rotation.to_json(t, trans.rotation);
        trans.scale.to_json(s, trans.scale);

        j = nlohmann::json{{"position", p}, {"rotation", t}, {"scale", s}};
    }

    void from_json(const nlohmann::json &j, JsonTransform &trans) {
        trans.position.from_json(j["position"], trans.position);
        trans.rotation.from_json(j["rotation"], trans.rotation);
        trans.scale.from_json(j["scale"], trans.scale);
    }
};


}// namespace taixu


#endif /* TAIXUENGINE_TRANSFORM_JSON_HPP */