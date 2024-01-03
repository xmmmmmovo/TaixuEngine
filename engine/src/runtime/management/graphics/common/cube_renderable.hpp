//
// Created by xmmmmmovo on 2023/5/21.
//

#ifndef ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_CUBE_RENDERABLE_HPP
#define ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_CUBE_RENDERABLE_HPP

#include <array>
#include <memory>

#include "common/designs/public_singleton.hpp"

namespace taixu {

class CubeRenderable : public PublicSingleton<CubeRenderable> {
    friend class PublicSingleton<CubeRenderable>;

private:
    static constexpr std::size_t CUBE_VERTEX_COUNT  = 24;
    static constexpr std::size_t CUBE_ELEMENT_COUNT = 36;

    static constexpr std::array<GLfloat, CUBE_VERTEX_COUNT> CUBE_VERTICES = {
            //   Coordinates
            -1.0f, -1.0f, 1.0f, //        7--------6
            1.0f,  -1.0f, 1.0f, //       /|       /|
            1.0f,  -1.0f, -1.0f,//      4--------5 |
            -1.0f, -1.0f, -1.0f,//      | |      | |
            -1.0f, 1.0f,  1.0f, //      | 3------|-2
            1.0f,  1.0f,  1.0f, //      |/       |/
            1.0f,  1.0f,  -1.0f,//      0--------1
            -1.0f, 1.0f,  -1.0f};

    static constexpr std::array<std::uint32_t, CUBE_ELEMENT_COUNT>
            CUBE_ELEMENTS = {// Right
                             1, 2, 6, 6, 5, 1,
                             // Left
                             0, 4, 7, 7, 3, 0,
                             // Top
                             4, 5, 6, 6, 7, 4,
                             // Bottom
                             0, 3, 2, 2, 1, 0,
                             // Back
                             0, 1, 5, 5, 4, 0,
                             // Front
                             3, 7, 6, 6, 2, 3};
};

}// namespace taixu

#endif// ENGINE_RUNTIME_MANAGEMENT_GRAPHICS_FRONTEND_CUBE_RENDERABLE_HPP
