//
// Created by xmmmmmovo on 2023/4/29.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_TYPES_HPP
#define ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_TYPES_HPP

#include <bitset>
#include <cstdint>

namespace taixu {

// ECS
using Entity                  = std::uint32_t;
// TODO: 后续改为动态分配
constexpr Entity MAX_ENTITIES = 65535;

using ComponentType = std::uint8_t;

constexpr ComponentType MAX_COMPONENTS = 32;
using Signature                        = std::bitset<MAX_COMPONENTS>;

using SystemIdType = std::uint64_t;

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_ECS_SYSTEM_TYPES_HPP
