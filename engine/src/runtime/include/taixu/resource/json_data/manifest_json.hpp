//
// Created by xmmmmmovo on 2023/7/9.
//

#pragma once

#include <string>

#include "resource/json/json_serializable.hpp"

namespace taixu {

struct Manifest {
    tx_string name{};
    tx_string version{};
    tx_string author{};
    tx_string description{};
};

}// namespace taixu

REFL_AUTO(type(taixu::Manifest), field(name, taixu::ISerializableStr()), field(version, taixu::ISerializableStr()),
          field(author, taixu::ISerializableStr()), field(description, taixu::ISerializableStr()))
