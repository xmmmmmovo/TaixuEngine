#ifndef ENTITY_COMPONENT_SYSTEM
#define ENTITY_COMPONENT_SYSTEM

#include <unordered_map>
#include <typeinfo>
#include <any>
#include <string>

#include <spdlog/spdlog.h>

#include "game_object.hpp"
#include "entity_component/mesh_component.hpp"

namespace taixu
{
template<typename T>
class Component {
public:
    Component(){}

    T getComponent(std::uint32_t uid) const {
        return map[uid];
    }

    void addComponent(std::uint32_t uid,T instance){
        map[uid]=instance;
    }

private:
    std::unordered_map<std::uint32_t, T> map;
};

class ECS
{
public:
    ECS(){};
    ~ECS(){};
    template<typename T>
    void addComponentType(T)
    {
        components[typeid(T)] = Component<T> map;
    };

    void deleteComponentType();

    void modify();
    //template<typename T>
    std::unordered_map<std::string, std::any> components;
};


}

#endif /* ENTITY_COMPONENT_SYSTEM */
