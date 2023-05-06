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
    ComponentType GetComponentType();

    template<typename T>
    void addComponent(Entity entity, T &&component);

    template<typename T>
    void removeComponent(Entity entity);

    template<typename T>
    T &getComponent(Entity entity);

    void entityDestroyed(Entity entity);

private:
    // Map from type string pointer to a component type
    std::unordered_map<const char *, ComponentType> _component_types{};

    // Map from type string pointer to a component array
    std::unordered_map<const char *, std::shared_ptr<IComponentArray>>
            _component_arrays{};

    // The component type to be assigned to the next registered component - starting at 0
    ComponentType _next_component_type{0};

    // Convenience function to get the statically cast pointer to the ComponentArray of type T.
    template<typename T>
    std::weak_ptr<ComponentArray<T>> getComponentArray();
};

}// namespace taixu

#include "component_manager.inl"

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_COMPONENT_MANAGER_HPP
