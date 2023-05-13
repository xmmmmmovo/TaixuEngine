#ifndef TAIXUENGINE_LEVEL_JSON
#define TAIXUENGINE_LEVEL_JSON


#include "game_object_json.hpp"
#include "resource/json/json_parser.hpp"
#include "transform_json.hpp"
namespace taixu {

enum class testEnumType { TYPE1, TYPE2, TYPE3 };


class JsonLevel {
public:
    std::string           level_name;
    std::string           level_path{"INVALID"};
    std::filesystem::path project_file_path{"INVALID"};

    std::vector<JsonGO> json_game_objects;
    //Vec3 p;
    //testEnumType type;
    void                to_json(nlohmann::json &j, JsonLevel lp) {
        j = nlohmann::json{{"level_name", lp.level_name},
                                          {"level_path", lp.level_path}};
    }

    void from_json(const nlohmann::json &j, JsonLevel &lp) {
        j.at("level_name").get_to(lp.level_name);
        j.at("level_path").get_to(lp.level_path);
        //j.at("type").get_to(lp.type);
    }

    void serialize() {
        if (level_path != "INVALID") {
            std::ofstream o(project_file_path / level_path);
            json          write;
            for (auto count : json_game_objects) {
                json j;
                count.to_json(j, count);
                count.project_file_path = project_file_path;
                //j = serialize(count);
                write += j;
                count.serialize();
            }
            json GOs{{"GOs", write}};
            o << std::setw(4) << GOs;
            o.close();
        }
    }

    void deserialize() {
        std::ifstream f(project_file_path / level_path);
        if (!f.is_open()) {
            spdlog::debug("Unable to load Asset configure file");
        }

        json data = json::parse(f);

        for (auto &i : data["GOs"].items()) {
            json const j = i.value();
            JsonGO     go;
            go.from_json(j, go);
            //std::filesystem::path temppath =   dir_path / new_asset.location;
            go.project_file_path = project_file_path;
            go.deserialize();
            json_game_objects.push_back(go);
        }
    }
};


}// namespace taixu
#endif /* TAIXUENGINE_LEVEL_JSON */