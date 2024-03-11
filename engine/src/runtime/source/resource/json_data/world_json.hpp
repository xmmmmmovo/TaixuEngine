//
// Created by xmmmmmovo on 2023/7/23.
//

#ifndef ENGINE_SRC_RUNTIME_RESOURCE_JSON_WORLD_JSON_HPP
#define ENGINE_SRC_RUNTIME_RESOURCE_JSON_WORLD_JSON_HPP

#include <refl.hpp>

#include <vector>

#include "resource/json/json_serializable.hpp"

namespace taixu {

struct World {
    struct Level {
        std::string level_name{};
        std::string level_path{};
    };

    struct Global {
        std::string render{};
    };

    std::string        name{};
    Global             global{};
    std::vector<Level> levels{};
};

}// namespace taixu

REFL_AUTO(type(taixu::World), field(name, taixu::ISerializableStr()),
          field(global, taixu::ISerializableObject()),
          field(levels, taixu::ISerializableList()))

REFL_AUTO(type(taixu::World::Level),
          field(level_name, taixu::ISerializableStr()),
          field(level_path, taixu::ISerializableStr()))

REFL_AUTO(type(taixu::World::Global), field(render, taixu::ISerializableStr()))

#endif// ENGINE_SRC_RUNTIME_RESOURCE_JSON_WORLD_JSON_HPP
