#ifndef TAIXUENGINE_WORLD_MANAGER
#define TAIXUENGINE_WORLD_MANAGER
#include <string>
#include <filesystem>
#include "level.hpp"

namespace taixu
{
class WorldManager
{
friend class ECS;
public:
std::string name{"taixu world"};
std::filesystem::path world_path = "INVALID";
void initialize()
{
    current_level=std::make_shared<Level>();
    current_level->initialize();
    
};

void saveLevel(){};
private:
std::shared_ptr<Level> current_level;
std::vector<Level>levels;

};


}

#endif /* TAIXUENGINE_WORLD_MANAGER */
