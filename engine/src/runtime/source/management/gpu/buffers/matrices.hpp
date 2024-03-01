//
// Created by xmmmmmovo on 2023/5/14.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_MATRICES_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_MATRICES_HPP

#include "common/math/matrix.hpp"
#include "common/math/vec.hpp"

namespace taixu {

struct Matrices {
    Mat4 projection;
    Mat4 view;
    Mat4 vp;

    Vec4 camera_pos;
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_MATRICES_HPP
