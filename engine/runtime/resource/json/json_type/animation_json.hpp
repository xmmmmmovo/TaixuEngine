// #ifndef TAIXUENGINE_ANIMATION_JSON_HPP
// #define TAIXUENGINE_ANIMATION_JSON_HPP

// #include "nlohmann/json.hpp"
// namespace taixu {
// class JsonAnimation {
// public:
//     std::string animation_path{"INVALID"};
//     std::string material_path{"INVALID"};

//     void to_json(nlohmann::json &j, const JsonMesh &m) {
//         j = nlohmann::json{{"animation_path", m.obj_path},
//                            {"material_path", m.material_path},
//                            };
//     }

//     void from_json(const nlohmann::json &j, JsonMesh &m) {
//         j.at("animation_path").get_to(m.obj_path);
//         j.at("material_path").get_to(m.material_path);
//     }
// };
//#endif /* TAIXUENGINE_ANIMATION_JSON_HPP */
