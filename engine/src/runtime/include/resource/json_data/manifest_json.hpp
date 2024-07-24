//
// Created by xmmmmmovo on 2023/7/9.
//

#pragma once

#include <string>

#include "resource/json/json_serializable.hpp"

namespace taixu {

struct Manifest {
    std::string name{};
    std::string version{};
    std::string author{};
    std::string description{};
};

}// namespace taixu

REFL_AUTO(type(taixu::Manifest), field(name, taixu::ISerializableStr()),
          field(version, taixu::ISerializableStr()),
          field(author, taixu::ISerializableStr()),
          field(description, taixu::ISerializableStr()))
