//
// Created by xmmmmmovo on 2023/3/28.
//

#ifndef TAIXUENGINE_IMVEC2_HPP
#define TAIXUENGINE_IMVEC2_HPP

#include <imgui.h>

namespace taixu {

ImVec2 operator-(const ImVec2 &a, const ImVec2 &b) {
    return {a.x - b.x, a.y - b.y};
}

bool operator!=(ImVec2 const &a, ImVec2 const &b) {
    return (a.x != b.x) || (a.y != b.y);
}

}// namespace taixu

#endif//TAIXUENGINE_IMVEC2_HPP
