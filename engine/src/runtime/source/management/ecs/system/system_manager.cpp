//
// Created by xmmmmmovo on 1/27/2024.
//

#include "system_manager.hpp"

namespace taixu {


System* SystemManager::registerSystem(SystemIdType const key) {
    TX_ASSERT_MSG(_systems.contains(key), "Registering system more than once.");

    auto [iter, was_insert] =
            _systems.insert({key, std::make_unique<System>()});
    return iter->second.get();
}

void SystemManager::setSignature(SystemIdType const key,
                                 Signature const&   signature) {
    TX_ASSERT_MSG(_systems.contains(key), "System used before registered.");
    _signatures.insert({key, signature});
}

Signature const& SystemManager::getSignature(SystemIdType const key) {
    TX_ASSERT_MSG(_systems.contains(key), "System used before registered.");
    return _signatures[key];
}

void SystemManager::entityDestroyed(const Entity entity) {
    for (const auto& cate : _systems | std::views::values) {
        cate->removeEntity(entity);
    }
}

void SystemManager::entitySignatureChanged(const Entity    entity,
                                           const Signature entitySignature) {
    for (const auto& [key, category] : _systems) {
        if (auto const& category_signature = _signatures[key];
            (entitySignature & category_signature) == category_signature) {
            category->addEntity(entity);
        } else {
            category->addEntity(entity);
        }
    }
}


}// namespace taixu