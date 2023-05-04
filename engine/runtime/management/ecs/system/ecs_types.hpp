//
// Created by xmmmmmovo on 2023/4/29.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_TYPES_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_TYPES_HPP

#include <bitset>
#include <cstdint>

namespace taixu {

// ECS
using EntityType                  = std::uint32_t;
// TODO: 后续改为动态分配
constexpr EntityType MAX_ENTITIES = 65535;

using ComponentType = std::uint8_t;

constexpr ComponentType MAX_COMPONENTS = 32;
using SignatureType                    = std::bitset<MAX_COMPONENTS>;

}// namespace taixu

#endif//ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_TYPES_HPP
