#ifndef TAIXUENGINE_LEVEL
#define TAIXUENGINE_LEVEL
#include <string>
#include <vector>
#include <filesystem>
#include "game_object.hpp"

namespace taixu
{
class Level
{
public:
friend class ECS;
std::string name{"level 1-1"};
std::filesystem::path levels_path="INVALID";
float grivaty{9.8};

void initialize(){
    GameObject cube;
    cube.set_id(GUID_Generator::generate_new_guid());
    GOs.push_back(cube);
    };
void tick(float delta_time=0.33);
private:
std::vector<GameObject> GOs;
};

}

#endif /* TAIXUENGINE_LEVEL */
