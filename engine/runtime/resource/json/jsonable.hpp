//
// Created by xmmmmmovo on 2023/2/26.
//

#ifndef TAIXUENGINE_JSONABLE_HPP
#define TAIXUENGINE_JSONABLE_HPP

#include <nlohmann/json.hpp>

#include "core/base/noncopyable.hpp"

namespace taixu {

using json = nlohmann::json;

template<typename T>
class IJsonable : private noncopyable {
public:
    virtual std::string toJson(T const& instance)     = 0;
    virtual T           fromJson(json const& jsonObj) = 0;
};

}// namespace taixu

#endif//TAIXUENGINE_JSONABLE_HPP