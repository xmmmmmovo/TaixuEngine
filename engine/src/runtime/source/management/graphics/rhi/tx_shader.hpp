//
// Created by xmmmmmovo on 1/25/2024.
//

#pragma once


#include <cstdint>

namespace taixu {

enum class ShaderType : uint8_t {
    NONE = 0,
    VERTEX,
    FRAGMENT,
    GEOMETRY,
    COMPUTE,
    HULL,
    DOMAIN,
    TEXTURE
};

class TXShader {};

}// namespace taixu