#ifndef TAIXUENGINE_WORLD_JSON
#define TAIXUENGINE_WORLD_JSON

#include "level_json.hpp"
#include "resource/json/json_type/global_json.hpp"

namespace taixu {

class JsonWorld {
public:
    JsonWorld() = default;

    std::vector<JsonLevel> json_levels;
    GlobalJson             global_json;

    std::filesystem::path file_path{"INVALID"};
    std::filesystem::path project_file_path{"INVALID"};

    void serialize() {
        if (file_path != "INVALID") {
            std::ofstream o((project_file_path / file_path).c_str());
            json          write;
            for (auto count : json_levels) {
                json j;
                count.to_json(j, count);
                count.project_file_path = project_file_path;
                //j = serialize(count);
                write += j;
                count.serialize();
            }
            json global;
            global_json.serialize();
            
            json levels{{"levels", write}};
            json render;
            render["render"] = global_json.render_global_path;;
            levels["global"] = render;
            o << std::setw(4) << levels;
            o.close();
        }
    }

    void deserialize() {
        std::ifstream f(project_file_path / file_path);
        if (!f.is_open()) {
            spdlog::debug("Unable to load Asset configure file");
        }

        json data = json::parse(f);

        for (auto &i : data["levels"].items()) {
            json const j = i.value();
            JsonLevel  level;
            level.from_json(j, level);
            level.project_file_path = project_file_path;
            level.deserialize();
            json_levels.push_back(level);
        }

        auto const &global_raw_json = data["global"];

        global_json.project_file_path = project_file_path;
        global_json.render_global_path =
                global_raw_json["render"].get<std::filesystem::path>();
        global_json.deserialize();
    }
};

}// namespace taixu


#endif /* TAIXUENGINE_WORLD_JSON */