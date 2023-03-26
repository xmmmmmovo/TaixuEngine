#ifndef TAIXUENGINE_ENTITY_COMPONENT
#define TAIXUENGINE_ENTITY_COMPONENT

#include <unordered_map>
#include <typeinfo>

namespace taixu
{
struct EntityComponent
{
public:
std::string name{};

};

struct MeshComponent:public EntityComponent
{
public:
//std::string name{};
bool visiable;
std::string mesh_path;
std::string material_path;
};

class EntityComponentMap {
public:
    EntityComponentMap(){}

    EntityComponent getComponent(std::uint32_t uid){
        return map[uid];
    }

    void addComponent(std::uint32_t uid,EntityComponent instance){
        map[uid]=instance;
    }

private:
    std::unordered_map<std::uint32_t, EntityComponent> map;
};




}
#endif /* TAIXUENGINE_ENTITY_COMPONENT */
