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
    std::unordered_map<std::size_t, Key> _index_to_key_map{};

public:
    Value &insertData(const Key &key, const Value &value) {
        if (contains(key)) { _values[_key_to_index_map[key]] = value; }

        _key_to_index_map[key]            = _values.size();
        _index_to_key_map[_values.size()] = key;
        _values.push_back(value);
        return _values.back();
    }

    Value &insertData(const Key &key, Value &&value) {
        if (contains(key)) {
            _values[_key_to_index_map[key]] = std::move(value);
        }
        _key_to_index_map[key]            = _values.size();
        _index_to_key_map[_values.size()] = key;
        _values.push_back(std::move(value));
        return _values.back();
    }

    void removeData(const Key &key) {
        assert(contains(key) && "Key does not exist.");

        std::size_t idx_of_removed_element = _key_to_index_map[key];
        std::size_t idx_of_last_element    = _values.size() - 1;
        if (idx_of_removed_element != idx_of_last_element) {
            // Swap the last element with the element to be removed.
            _values[idx_of_removed_element] =
                    std::move(_values[idx_of_last_element]);

            Key key_of_last_element = _index_to_key_map[idx_of_last_element];
            _key_to_index_map[key_of_last_element]    = idx_of_removed_element;
            _index_to_key_map[idx_of_removed_element] = key_of_last_element;
        }
        _values.pop_back();
        _key_to_index_map.erase(key);
        _index_to_key_map.erase(idx_of_last_element);
    }

    Value &getData(const Key &key) {
        assert(contains(key) && "Key does not exist.");
        return _values[_key_to_index_map[key]];
    }

    Value const &getData(const Key &key) const {
        assert(contains(key) && "Key does not exist.");
        return _values[_key_to_index_map[key]];
    }

    Value &operator[](const Key &key) { return getData(key); }

    [[nodiscard]] std::size_t size() const { return _values.size(); }

    [[nodiscard]] bool contains(const Key &key) const {
        return _key_to_index_map.find(key) != _key_to_index_map.end();
    }

    void clear() {
        _values.clear();
        _key_to_index_map.clear();
        _index_to_key_map.clear();
    }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_CORE_CONTAINER_MAP_VECTOR_HPP
