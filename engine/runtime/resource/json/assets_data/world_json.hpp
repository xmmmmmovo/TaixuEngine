#ifndef TAIXUENGINE_WORLD_JSON
#define TAIXUENGINE_WORLD_JSON

#include "resource/json/jsonable.hpp"
#include "resource/json/json_parser.hpp"
#include "level_json.hpp"
namespace taixu
{

class JsonWorld
{
public:
    JsonWorld() = default;

    std::vector<JsonLevel> json_levels;
    
    std::filesystem::path file_path{"INVALID"};
    std::filesystem::path asset_file_path{"INVALID"};
    void serialize()
    {
        if (file_path != "INVALID")
        {
            std::ofstream o((asset_file_path/file_path).c_str());
            json write;
            for (auto count : json_levels) 
            {   
                json j;
                count.to_json(j, count);
                count.asset_file_path = asset_file_path;
                //j = serialize(count);
                write+=j;
                count.serialize();
            }
            json levels{{"levels", write}};
            o << std::setw(4) << levels;
            o.close();
        }
    }

    void deserialize()
    {
        std::ifstream f(asset_file_path/file_path);
        if (!f.is_open()) {
            spdlog::debug("Unable to load Asset configure file");
        }

        json data = json::parse(f);

        for (auto &i : data["levels"].items()) {
            json const j                = i.value();
            JsonLevel level;
            level.from_json(j, level);
            //std::filesystem::path temppath =   dir_path / new_asset.location;
            level.asset_file_path = asset_file_path;
            level.deserialize();
            json_levels.push_back(level);
        }
    }
};

}


#endif /* TAIXUENGINE_WORLD_JSON */
