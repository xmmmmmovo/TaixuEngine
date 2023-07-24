//
// Created by xmmmmmovo on 2023/2/26.
//

#ifndef TAIXUENGINE_SRC_RUNTIME_RESOURCE_SERIALIZABLE_HPP
#define TAIXUENGINE_SRC_RUNTIME_RESOURCE_SERIALIZABLE_HPP

#include <refl.hpp>

namespace taixu {

class ISerializableStr : refl::attr::usage::field {};
class ISerializableNumber : refl::attr::usage::field {};
class ISerializableBool : refl::attr::usage::field {};
class ISerializableNULL : refl::attr::usage::field {};
class ISerializableObject : refl::attr::usage::field {};
class ISerializableList : refl::attr::usage::field {};

}// namespace taixu

#endif// TAIXUENGINE_SRC_RUNTIME_RESOURCE_SERIALIZABLE_HPP
