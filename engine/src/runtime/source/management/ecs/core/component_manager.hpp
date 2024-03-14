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
    void registerComponent() {
        const char* type_name = typeid(T).name();

        TX_ASSERT_MSG(_component_types.contains(type_name),
                      "Registering component type more than once.");

        // Add this component type to the component type map
        _component_types.insert({type_name, _next_component_type});

        // Create a ComponentArray pointer and add it to the component arrays
        // map
        _component_arrays.insert(
                {type_name, std::make_unique<ComponentArray<T>>()});

        // Increment the value so that the next component registered will be
        // different
        ++_next_component_type;
    }

    template<typename T>
    ComponentType getComponentType() {
        const char* type_name = typeid(T).name();

        TX_ASSERT_MSG(_component_types.contains(type_name),
                      "Component not registered before use.");

        // Return this component's type - used for creating signatures
        return _component_types[type_name];
    }

    template<typename T>
    void addComponent(Entity entity, T&& component) {
        // Add a component to the array for an entity
        getComponentArray<T>()->insertData(entity, std::forward<T>(component));
    }

    template<typename T>
    void removeComponent(Entity entity) {
        // Remove a component from the array for an entity
        getComponentArray<T>()->removeData(entity);
    }

    template<typename T>
    T& getComponent(Entity entity) {
        // Get a reference to a component from the array for an entity
        return getComponentArray<T>()->getData(entity);
    }

    template<typename T>
    bool contains(Entity entity) {
        // Check if an entity has a component (based on component type)
        TX_ASSERT_MSG(_component_types.contains(typeid(T).name()),
                      "Component not registered before use.");
        return getComponentArray<T>()->contains(entity);
    }

    void entityDestroyed(const Entity entity) const {
        // Notify each component array that an entity has been destroyed
        // If it has a component for that entity, it will remove it
        for (const auto& val : _component_arrays | std::views::values) {
            auto const& component = val;
            component->entityDestroyed(entity);
        }
    }

private:
    // Map from type string pointer to a component type
    std::unordered_map<const char*, ComponentType> _component_types{};

    // Map from type string pointer to a component array
    std::unordered_map<const char*, std::unique_ptr<IComponentArray>>
            _component_arrays{};

    // The component type to be assigned to the next registered component -
    // starting at 0
    ComponentType _next_component_type{0};

    // Convenience function to get the statically cast pointer to the
    // ComponentArray of type T.
    template<typename T>
    ComponentArray<T>* getComponentArray() {
        const char* type_name = typeid(T).name();

        TX_ASSERT_MSG(_component_types.contains(type_name),
                      "Component not registered before use.");

        return static_cast<ComponentArray<T>*>(
                _component_arrays[type_name].get());
    }
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_ECS_COMPONENT_MANAGER_HPP
