//
// Created by xmmmmmovo on 2023/5/6.
//

#ifndef ENGINE_RUNTIME_CORE_CONTAINER_MAP_ARRAY_HPP
#define ENGINE_RUNTIME_CORE_CONTAINER_MAP_ARRAY_HPP

#include <array>
#include <cassert>
#include <cstddef>
#include <unordered_map>
#include <vector>

#include "common/base/macro.hpp"

namespace taixu {

template<typename Key, typename Value, std::size_t Size>
class MapArray final {
    // The packed array (of generic type T),
    // set to a specified maximum amount, matching the maximum number
    // of entities allowed to exist simultaneously, so that each entity
    // has a unique spot.
    using Array = std::array<Value, Size>;
    PROTOTYPE_ONLY_GETTER(private, Array, values)

private:
    // Map from key ID to an array index.
    std::unordered_map<Key, std::size_t> _key_to_index_map{};
    // Map from an array index to key ID.
    std::unordered_map<std::size_t, Key> _index_to_key_map{};
    // Total size of valid entries in the array.
    std::size_t                          _size{0};

public:
    void insertData(const Key& key, const Value& value) noexcept {
        if (contains(key)) {
            _values[_key_to_index_map[key]] = value;
            return;
        }
        std::size_t new_idx        = _size;
        _key_to_index_map[key]     = new_idx;
        _index_to_key_map[new_idx] = key;
        _values[new_idx]           = value;
        _size++;
    }

    void insertData(const Key& key, Value&& value) noexcept {
        if (contains(key)) {
            _values[_key_to_index_map[key]] = std::move(value);
            return;
        }
        std::size_t new_idx        = _size;
        _key_to_index_map[key]     = new_idx;
        _index_to_key_map[new_idx] = key;
        _values[new_idx]           = std::move(value);
        _size++;
    }

    void removeData(const Key& key) {
        assert(contains(key) && "Key does not exist.");
        std::size_t idx_of_removed_element = _key_to_index_map[key];
        std::size_t idx_of_last_element    = _size - 1;

        if (idx_of_removed_element == idx_of_last_element) {
            _values[idx_of_removed_element].~Value();
        } else {
            _values[idx_of_removed_element] =
                    std::move(_values[idx_of_last_element]);

            Key key_of_last_element = _index_to_key_map[idx_of_last_element];
            _key_to_index_map[key_of_last_element]    = idx_of_removed_element;
            _index_to_key_map[idx_of_removed_element] = key_of_last_element;
        }

        _key_to_index_map.erase(key);
        _index_to_key_map.erase(idx_of_last_element);

        --_size;
    }

    Value& getData(const Key& key) {
        assert(contains(key) && "Key does not exist.");
        return _values[_key_to_index_map[key]];
    }

    Value const& getData(const Key& key) const {
        assert(contains(key) && "Key does not exist.");
        return _values[_key_to_index_map[key]];
    }

    [[nodiscard]] std::size_t size() const { return _size; }

    bool contains(const Key& key) const {
        return _key_to_index_map.find(key) != _key_to_index_map.end();
    }

    void clear() {
        for (std::size_t i = 0; i < _size; ++i) { _values[i].~Value(); }
        _key_to_index_map.clear();
        _index_to_key_map.clear();
        _size = 0;
    }
};

}// namespace taixu

#endif// ENGINE_RUNTIME_CORE_CONTAINER_MAP_ARRAY_HPP
