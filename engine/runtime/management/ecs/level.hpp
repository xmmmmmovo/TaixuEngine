#ifndef TAIXUENGINE_LEVEL
#define TAIXUENGINE_LEVEL
#include "game_object.hpp"
#include <filesystem>
#include <string>
#include <vector>

namespace taixu {
class Level {
public:
    friend class ECS;
    std::string           name{"level 1-1"};
    std::filesystem::path levels_path = "INVALID";
    float                 grivaty{9.8};

    void initialize() {
        GameObject cube;
        cube.set_id(GuidGenerator::generateNewGuid());
        GOs.push_back(cube);

        GameObject teapot;
        teapot.set_id(GuidGenerator::generateNewGuid());
        GOs.push_back(teapot);

    };
    void tick(float delta_time = 0.33);

private:
    std::vector<GameObject> GOs;
};

}// namespace taixu

#endif /* TAIXUENGINE_LEVEL */
