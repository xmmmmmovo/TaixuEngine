#ifndef TAIXUENGINE_LEVEL_JSON
#define TAIXUENGINE_LEVEL_JSON


#include "game_object_json.hpp"
#include "light_json.hpp"
namespace taixu {

enum class testEnumType { TYPE1, TYPE2, TYPE3 };

class JsonLevel {
public:
    std::string           level_name;
    std::string           level_path{"INVALID"};
    std::filesystem::path project_file_path{"INVALID"};

    std::vector<JsonGO> json_game_objects;
    std::vector<JsonLight> json_lights;

    void to_json(nlohmann::json &j, JsonLevel lp) {
        j = nlohmann::json{{"level_name", lp.level_name},
                           {"level_path", lp.level_path}};
    }

    void from_json(const nlohmann::json &j, JsonLevel &lp) {
        j.at("level_name").get_to(lp.level_name);
        j.at("level_path").get_to(lp.level_path);
    }

    void serialize() {
        if (level_path != "INVALID") {
            std::ofstream o(project_file_path / level_path);
            json          write;
            for (auto count : json_game_objects) {
                json j;
                count.to_json(j, count);
                count.project_file_path = project_file_path;
                write += j;
                count.serialize();
            }

            json          lwrite;
            for (auto count : json_lights) {
                json j;
                count.to_json(j, count);
                count.project_file_path = project_file_path;
                lwrite += j;
                count.serialize();
            }
            json info{{"GOs", write},
                {"Lights", lwrite}};
            o << std::setw(4) << info;

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
            go.project_file_path = project_file_path;
            go.deserialize();
            json_game_objects.push_back(go);
        }

        for (auto &k : data["Lights"].items()) {
            json const j = k.value();
            JsonLight     light;
            light.from_json(j, light);
            light.project_file_path = project_file_path;
            light.deserialize();
            json_lights.push_back(light);
        }
    }
};


}// namespace taixu
#endif /* TAIXUENGINE_LEVEL_JSON */