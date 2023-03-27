#ifndef TAIXUENGINE_ENTITY_COMPONENT
#define TAIXUENGINE_ENTITY_COMPONENT

#include <unordered_map>
#include <typeinfo>

namespace taixu
{
class EntityComponent
{
public:
virtual ~EntityComponent()=default;
};

class MeshComponent:public EntityComponent
{
public:
MeshComponent(bool renderable,std::string path1,std::string path2)
:visible(renderable),mesh_path(path1),material_path(path2){}
//std::string name{};
bool visible;
std::string mesh_path;
std::string material_path;
};

class EntityComponentMap {
public:
    EntityComponentMap(){}

    EntityComponent* getComponent(std::uint32_t uid){
        return map[uid];
    }

    void addComponent(std::uint32_t uid,EntityComponent* instance){
        map[uid]=instance;
    }

private:
    std::unordered_map<std::uint32_t, EntityComponent*> map;
};




}
#endif /* TAIXUENGINE_ENTITY_COMPONENT */
