//
// Created by xmmmmmovo on 2023/2/23.
//

#ifndef TAIXUENGINE_OGL_TEXTURE_HPP
#define TAIXUENGINE_OGL_TEXTURE_HPP

#include <glad/glad.h>

#include <spdlog/spdlog.h>
#include <stb_image.h>
#include <string_view>

#include "management/graphics/render/texture2D.hpp"

namespace taixu {

/**
 * @brief OpenGL texture
 */
class OGLTexture : public ITexture2D {
private:
    int      _width{0};
    int      _height{0};
    int      _n_channels{0};
    uint32_t _texture_id{0};

private:
    void createTexture(stbi_uc *data, int width, int height, int n_channels,
                       GLint filter_mode, GLint what_happens_at_edge);

public:
    /**
     * @brief OpenGL Texture constructor
     * @param path image path
     * @param filter_mode if not use in render, please use GL_NEAREST, default value is GL_LINEAR
     * @param what_happens_at_edge default value is GL_REPEAT
     */
    explicit OGLTexture(const std::string_view &path, GLint                   filter_mode = GL_LINEAR,
                        GLint what_happens_at_edge          = GL_REPEAT);

    explicit OGLTexture(stbi_uc *data, int width, int height, int n_channels,GLint                   filter_mode = GL_LINEAR,
                        GLint what_happens_at_edge          = GL_REPEAT);

    int      getWidth() const override;
    int      getHeight() const override;
    uint32_t getTextureID() const override;
    void     bind(uint32_t slot) const override;
    bool     operator==(const ITexture2D &other) const override;

    ~OGLTexture() override;
};

}// namespace taixu

#endif//TAIXUENGINE_OGL_TEXTURE_HPP
