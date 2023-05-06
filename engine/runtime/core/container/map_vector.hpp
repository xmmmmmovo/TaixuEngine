//
// Created by xmmmmmovo on 2023/5/6.
//

#ifndef ENGINE_RUNTIME_CORE_CONTAINER_MAP_VECTOR_HPP
#define ENGINE_RUNTIME_CORE_CONTAINER_MAP_VECTOR_HPP

#include <unordered_map>
#include <vector>

#include "core/base/macro.hpp"

namespace taixu {

template<typename Key, typename Value>
class MapVector final {
    PROTOTYPE_ONLY_GETTER_CONST(private, std::vector<Value>, values)

private:
    std::unordered_map<Key, std::size_t> _key_to_index_map{};

public:
    void insertData(const Key &key, const Value &value) {
        std::size_t new_idx    = _values.size();
        _key_to_index_map[key] = new_idx;
        _values.emplace_back(value);
    }

    void insertData(const Key &key, Value &&value) {}

    void removeData(const Key &key) {}

//    Value       &getData(const Key &key) {}
//    Value const &getData(const Key &key) const {}

    [[nodiscard]] std::size_t size() const { return _values.size(); }
};
}// namespace taixu

#endif//ENGINE_RUNTIME_CORE_CONTAINER_MAP_VECTOR_HPP
