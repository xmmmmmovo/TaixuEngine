#ifndef TAIXUENGINE_ENTITY_COMPONENT
#define TAIXUENGINE_ENTITY_COMPONENT

#include <cstdint>
#include <typeinfo>
#include <unordered_map>

#include "core/base/macro.hpp"
#include "core/container/map_array.hpp"
#include "ecs_types.hpp"
#include "management/ecs/core/entity_manager.hpp"
#include "management/ecs/object/guid_genenrator.hpp"

namespace taixu {

class IComponentArray {
public:
    virtual ~IComponentArray()                  = default;
    virtual void entityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
    void insertData(Entity entity, T &&component) {
        assert(_map_array.contains(entity) == false &&
               "Component added to same entity more than once.");

        _map_array.insertData(entity, std::move(component));
    }

    void removeData(Entity entity) { _map_array.removeData(entity); }

    T &getData(Entity entity) { return _map_array.getData(entity); }

    void entityDestroyed(Entity entity) override {
        if (_map_array.contains(entity)) { _map_array.removeData(entity); }
    }

private:
    MapArray<Entity, T, MAX_ENTITIES> _map_array;
};

}// namespace taixu

#endif /* TAIXUENGINE_ENTITY_COMPONENT */