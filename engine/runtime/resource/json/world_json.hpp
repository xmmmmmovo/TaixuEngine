#ifndef TAISUENGINE_WORLD_JSON
#define TAISUENGINE_WORLD_JSON

#include "jsonable.hpp"
#include "json_parser.hpp"
#include "level_json.hpp"
namespace taixu
{




class jsonWorld : public IJsonable
{
public:
    jsonWorld() = default;

    //std::string level_name;
    //std::string level_path;

    // void to_json(nlohmann::json& j,  LevelProperty lp) {
    //     j = nlohmann::json{{"level_name", lp.level_name}, {"level_path", lp.level_path},{"type", lp.type}};
    //     lp.p.to_json(j["p"], lp.p);
    // }

    // void from_json(const nlohmann::json& j, LevelProperty& lp) {
    //     j.at("level_name").get_to(lp.level_name);
    //     j.at("level_path").get_to(lp.level_path);
    //     j.at("type").get_to(lp.type);
    //     lp.p.from_json(j["p"], lp.p);
    // }
    
    std::vector<LevelProperty> json_levels;

    
    std::filesystem::path file_path{"INVALID"};
    void toJson()
    {
        if (file_path != "INVALID")
        {
            std::ofstream o(file_path);
            json write;
            for (auto count : json_levels) 
            {   
                json j;
                count.to_json(j, count);
                //j = serialize(count);
                write+=j;
            }
            json levels{{"levels", write}};
            o << std::setw(4) << levels;
            o.close();
        }
    }
};



}


#endif /* TAISUENGINE_WORLD_JSON */
