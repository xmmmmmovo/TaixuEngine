//
// Created by xmmmmmovo on 2023/7/10.
//

#ifndef ENGINE_RUNTIME_RESOURCE_JSON_COMMON_TYPES_HPP
#define ENGINE_RUNTIME_RESOURCE_JSON_COMMON_TYPES_HPP

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <refl.hpp>

#include "serializable.hpp"

// register glm types

REFL_AUTO(type(glm::vec2), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()))

REFL_AUTO(type(glm::vec3), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()),
          field(z, taixu::ISerializableNumber()))

REFL_AUTO(type(glm::vec4), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()),
          field(z, taixu::ISerializableNumber()),
          field(w, taixu::ISerializableNumber()))

REFL_AUTO(type(glm::ivec2), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()))

REFL_AUTO(type(glm::ivec3), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()),
          field(z, taixu::ISerializableNumber()))

REFL_AUTO(type(glm::ivec4), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()),
          field(z, taixu::ISerializableNumber()),
          field(w, taixu::ISerializableNumber()))

REFL_AUTO(type(glm::quat), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()),
          field(z, taixu::ISerializableNumber()),
          field(w, taixu::ISerializableNumber()))

#endif// ENGINE_RUNTIME_RESOURCE_JSON_COMMON_TYPES_HPP
