#ifndef TAIXUENGINE_ENTITY_COMPONENT
#define TAIXUENGINE_ENTITY_COMPONENT

#include <unordered_map>
#include <typeinfo>

namespace taixu
{
class EntityComponent
{
public:
virtual void tick()=0;
virtual ~EntityComponent()=default;
};



class EntityComponentMap {
public:
    EntityComponentMap(){}

   [[nodiscard]] EntityComponent* getComponent(std::uint32_t uid){

        return map[uid];
    }

    void addComponent(std::uint32_t uid, EntityComponent* instance){
        map[uid]=instance;
    }

    std::unordered_map<std::uint32_t, EntityComponent*> map;
};




}
#endif /* TAIXUENGINE_ENTITY_COMPONENT */
