#ifndef TAIXUENGINE_ENTITY_COMPONENT
#define TAIXUENGINE_ENTITY_COMPONENT

#include <typeinfo>
#include <unordered_map>

namespace taixu {

class EntityComponent {
public:
    virtual std::uint32_t getGO() = 0;
    virtual void          tick()  = 0;
    virtual ~EntityComponent()    = default;
};

class EntityComponentMap {
public:
    EntityComponentMap() = default;

    [[nodiscard]] std::shared_ptr<EntityComponent>
    getComponent(std::uint32_t guid) {
        int mark = 0;
        for (auto &component : map) {
            if (component->getGO() == guid) {
                break;
            } else {
                mark++;
            }
        }
        return map[mark];
    }

    void addComponent(const std::shared_ptr<EntityComponent> &instance) {
        map.push_back(instance);
    }

    std::vector<std::shared_ptr<EntityComponent>> map;
};


}// namespace taixu
#endif /* TAIXUENGINE_ENTITY_COMPONENT */
