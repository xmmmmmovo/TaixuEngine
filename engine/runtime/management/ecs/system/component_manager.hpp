//
// Created by xmmmmmovo on 2023/4/29.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_COMPONENT_MANAGER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_COMPONENT_MANAGER_HPP

#include "component_array.hpp"

namespace taixu {
class ComponentManager {
public:
    template<typename T>
    void registerComponent();

    template<typename T>
    ComponentType GetComponentType() {
        const char *type_name = typeid(T).name();

        assert(_component_types.find(type_name) != _component_types.end() &&
               "Component not registered before use.");

        // Return this component's type - used for creating signatures
        return _component_types[type_name];
    }

    template<typename T>
    void AddComponent(EntityType entity, T component) {
        // Add a component to the array for an entity
        getComponentArray<T>()->InsertData(entity, component);
    }

    template<typename T>
    void RemoveComponent(EntityType entity) {
        // Remove a component from the array for an entity
        getComponentArray<T>()->RemoveData(entity);
    }

    template<typename T>
    T &getComponent(EntityType entity) {
        // Get a reference to a component from the array for an entity
        return getComponentArray<T>()->GetData(entity);
    }

    void entityDestroyed(EntityType entity);

private:
    // Map from type string pointer to a component type
    std::unordered_map<const char *, ComponentType> _component_types{};

    // Map from type string pointer to a component array
    std::unordered_map<const char *, std::shared_ptr<IComponentArray>>
            _component_arrays{};

    // The component type to be assigned to the next registered component - starting at 0
    ComponentType _next_component_type{};

    // Convenience function to get the statically cast pointer to the ComponentArray of type T.
    template<typename T>
    std::weak_ptr<ComponentArray<T>> getComponentArray();
};

}// namespace taixu

#include "component_manager.inl"

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_COMPONENT_MANAGER_HPP
