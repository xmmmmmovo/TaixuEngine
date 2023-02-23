//
// Created by xmmmmmovo on 2023/2/23.
//

#ifndef TAIXUENGINE_OGLTEXTURE_HPP
#define TAIXUENGINE_OGLTEXTURE_HPP

#include <glad/glad.h>

#include <spdlog/spdlog.h>
#include <stb_image.h>

#include <string_view>

#include "graphics/render/texture.hpp"

namespace taixu {

class OGLTexture : public ITexture {
private:
    int      width{0};
    int      height{0};
    int      n_channels{0};
    uint32_t texture_id{0};

public:
    explicit OGLTexture(const std::string_view &path);

    int      getWidth() const override;
    int      getHeight() const override;
    uint32_t getTextureID() const override;
    void     bind(uint32_t slot) const override;
    bool     operator==(const ITexture &other) const override;
};

}// namespace taixu

#endif//TAIXUENGINE_OGLTEXTURE_HPP
