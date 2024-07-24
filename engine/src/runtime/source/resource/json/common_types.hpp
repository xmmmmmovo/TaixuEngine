//
// Created by xmmmmmovo on 2023/7/10.
//


#pragma once

#include "common/math/fwd.hpp"
#include "common/math/vec.hpp"

#include <refl.hpp>

#include "serializable.hpp"

// register glm types

REFL_AUTO(type(Vec2), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()))

REFL_AUTO(type(Vec3), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()),
          field(z, taixu::ISerializableNumber()))

REFL_AUTO(type(Vec4), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()),
          field(z, taixu::ISerializableNumber()),
          field(w, taixu::ISerializableNumber()))

REFL_AUTO(type(IVec2), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()))

REFL_AUTO(type(IVec3), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()),
          field(z, taixu::ISerializableNumber()))

REFL_AUTO(type(IVec4), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()),
          field(z, taixu::ISerializableNumber()),
          field(w, taixu::ISerializableNumber()))

REFL_AUTO(type(Quat), field(x, taixu::ISerializableNumber()),
          field(y, taixu::ISerializableNumber()),
          field(z, taixu::ISerializableNumber()),
          field(w, taixu::ISerializableNumber()))
