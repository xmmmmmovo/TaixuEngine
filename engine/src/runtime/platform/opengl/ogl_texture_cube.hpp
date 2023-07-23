//
// Created by xmmmmmovo on 2023/5/15.
//

#ifndef ENGINE_RUNTIME_PLATFORM_OPENGL_OGL_TEXTURE_CUBE_HPP
#define ENGINE_RUNTIME_PLATFORM_OPENGL_OGL_TEXTURE_CUBE_HPP

#include <runtime/management/graphics/render/texture_cube.hpp>
#include <runtime/platform/opengl/ogl_texture2d.hpp>
#include <runtime/resource/helper/image_helper.hpp>

namespace taixu {

class OGLTextureCube : public ITextureCube {
private:
    uint32_t _texture_id{0};

public:
    explicit OGLTextureCube(std::string const &posx, std::string const &negx,
                            std::string const &posy, std::string const &negy,
                            std::string const &posz, std::string const &negz) {
        glGenTextures(1, &_texture_id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _texture_id);

        auto load_and_bind = [](std::string const &path, GLenum target) {
            int  width, height, channels;
            auto data = loadImage(path, &width, &height, &channels, 0, false);
            if (data) {
                glTexImage2D(target, 0, mapImageToGLReadType(channels), width,
                             height, 0, mapImageToGLReadType(channels),
                             GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            } else {
                spdlog::error("Unable to load image: {}", path);
                stbi_image_free(data);
            }
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER,
                            GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER,
                            GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,
                            GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T,
                            GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R,
                            GL_CLAMP_TO_EDGE);
        };

        load_and_bind(posx, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
        load_and_bind(negx, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
        load_and_bind(posy, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
        load_and_bind(negy, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
        load_and_bind(posz, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
        load_and_bind(negz, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
    }

    [[nodiscard]] std::uint32_t getTextureID() const override {
        return _texture_id;
    }

    void bind(std::uint32_t slot) const override {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _texture_id);
    }

    bool operator==(const ITextureCube &other) const override {
        return _texture_id == other.getTextureID();
    }

    ~OGLTextureCube() override { glDeleteTextures(1, &_texture_id); }
};

}// namespace taixu

#endif//ENGINE_RUNTIME_PLATFORM_OPENGL_OGL_TEXTURE_CUBE_HPP
