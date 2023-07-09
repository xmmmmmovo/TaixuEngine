//
// Created by xmmmmmovo on 2023/2/26.
//

#ifndef TAIXUENGINE_JSONABLE_HPP
#define TAIXUENGINE_JSONABLE_HPP


#include <refl.hpp>

namespace taixu {

class IJsonable : refl::attr::usage::field, refl::attr::usage::function {};

}// namespace taixu

#endif// TAIXUENGINE_JSONABLE_HPP
