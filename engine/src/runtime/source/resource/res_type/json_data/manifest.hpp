//
// Created by xmmmmmovo on 2023/7/9.
//

#ifndef ENGINE_RUNTIME_RESOURCE_JSON_PROJECT_JSON_HPP
#define ENGINE_RUNTIME_RESOURCE_JSON_PROJECT_JSON_HPP

#include <string>

#include <refl.hpp>

#include "resource/json/serializable.hpp"

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

#endif// ENGINE_RUNTIME_RESOURCE_JSON_PROJECT_JSON_HPP
