//
// Created by xmmmmmovo on 2023/4/29.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_COMPONENT_MANAGER_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_COMPONENT_MANAGER_HPP

#include "management/ecs/entity_component/entity_component.hpp"

namespace taixu {
class ComponentManager {
public:
    template<typename T>
    void RegisterComponent() {
        const char *typeName = typeid(T).name();

        assert(mComponentTypes.find(typeName) == mComponentTypes.end() &&
               "Registering component type more than once.");

        // Add this component type to the component type map
        mComponentTypes.insert({typeName, mNextComponentType});

        // Create a ComponentArray pointer and add it to the component arrays map
        mComponentArrays.insert(
                {typeName, std::make_shared<ComponentArray<T>>()});

        // Increment the value so that the next component registered will be different
        ++mNextComponentType;
    }

    template<typename T>
    ComponentType GetComponentType() {
        const char *typeName = typeid(T).name();

        assert(mComponentTypes.find(typeName) != mComponentTypes.end() &&
               "Component not registered before use.");

        // Return this component's type - used for creating signatures
        return mComponentTypes[typeName];
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        // Add a component to the array for an entity
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        // Remove a component from the array for an entity
        GetComponentArray<T>()->RemoveData(entity);
    }

    template<typename T>
    T &GetComponent(Entity entity) {
        // Get a reference to a component from the array for an entity
        return GetComponentArray<T>()->GetData(entity);
    }

    void EntityDestroyed(Entity entity) {
        // Notify each component array that an entity has been destroyed
        // If it has a component for that entity, it will remove it
        for (auto const &pair : mComponentArrays) {
            auto const &component = pair.second;

            component->EntityDestroyed(entity);
        }
    }

private:
    // Map from type string pointer to a component type
    std::unordered_map<const char *, ComponentType> mComponentTypes{};

    // Map from type string pointer to a component array
    std::unordered_map<const char *, std::shared_ptr<IComponentArray>>
            mComponentArrays{};

    // The component type to be assigned to the next registered component - starting at 0
    ComponentType mNextComponentType{};

    // Convenience function to get the statically cast pointer to the ComponentArray of type T.
    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray() {
        const char *typeName = typeid(T).name();

        assert(mComponentTypes.find(typeName) != mComponentTypes.end() &&
               "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>(
                mComponentArrays[typeName]);
    }
};
}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_COMPONENT_MANAGER_HPP