#ifndef TAIXUENGINE_MESH_JSON_HPP
#define TAIXUENGINE_MESH_JSON_HPP

#include "transform_json.hpp"
namespace taixu {

class JsonRenderable {
public:
    std::string obj_path{"INVALID"};
    bool        visiable;

    void to_json(nlohmann::json &j, const JsonRenderable &m) {
        j = nlohmann::json{{"obj_path", m.obj_path}, {"visiable", m.visiable}};
    }

    void from_json(const nlohmann::json &j, JsonRenderable &m) {
        j.at("obj_path").get_to(m.obj_path);
        j.at("visiable").get_to(m.visiable);
    }
};


}// namespace taixu
#endif /* TAIXUENGINE_MESH_JSON_HPP */