#ifndef TAISUENGINE_LEVEL_JSON
#define TAISUENGINE_LEVEL_JSON


#include "jsonable.hpp"
#include "json_parser.hpp"

namespace taixu
{

enum class testEnumType{TYPE1,TYPE2,TYPE3};
class Vec3 {
public:
    // float x;
    // float y;
    // float z;
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

class LevelProperty {
public:
    std::string level_name;
    std::string level_path;
    Vec3 p;
    testEnumType type;
    void to_json(nlohmann::json& j,  LevelProperty lp) {
        j = nlohmann::json{{"level_name", lp.level_name}, {"level_path", lp.level_path},{"type", lp.type}};
        lp.p.to_json(j["p"], lp.p);
    }

    void from_json(const nlohmann::json& j, LevelProperty& lp) {
        j.at("level_name").get_to(lp.level_name);
        j.at("level_path").get_to(lp.level_path);
        j.at("type").get_to(lp.type);
        lp.p.from_json(j["p"], lp.p);
    }
};


}
#endif /* TAISUENGINE_LEVEL_JSON */
