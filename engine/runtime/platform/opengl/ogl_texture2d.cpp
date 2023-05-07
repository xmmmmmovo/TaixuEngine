//
// Created by xmmmmmovo on 2023/2/23.
//

#include "ogl_texture2d.hpp"

#include "resource/helper/image_helper.hpp"
#include <filesystem>

namespace taixu {

GLint mapImageToGLReadType(int channels) {
    if (1 == channels) { return GL_RED; }
    if (2 == channels) { return GL_RG; }
    if (3 == channels) { return GL_RGB; }
    if (4 == channels) { return GL_RGBA; }
    return 0;
}

OGLTexture2D::OGLTexture2D(const std::filesystem::path &path, GLint filter_mode,
                           GLint what_happens_at_edge) {
    stbi_uc *data = loadImage(path, &_width, &_height, &_n_channels);
    if (data == nullptr) {
        spdlog::error("OGLTexture::OGLTexture: load image failed");
        return;
    }
    createTexture(data, _width, _height, _n_channels, filter_mode,
                  what_happens_at_edge);
    stbi_image_free(data);
}

OGLTexture2D::OGLTexture2D(stbi_uc *data, int width, int height, int n_channels,
                           GLint filter_mode, GLint what_happens_at_edge)
    : _width(width), _height(height), _n_channels(n_channels) {
    if (data == nullptr) {
        spdlog::error("OGLTexture::OGLTexture: load image failed");
        return;
    }
    createTexture(data, width, height, n_channels, filter_mode,
                  what_happens_at_edge);
    stbi_image_free(data);
}

void OGLTexture2D::createTexture(stbi_uc *data, int width, int height,
                                 int n_channels, GLint filter_mode,
                                 GLint what_happens_at_edge) {

    glGenTextures(1, &_texture_id);
    glBindTexture(GL_TEXTURE_2D, _texture_id);

    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, what_happens_at_edge);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, what_happens_at_edge);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_mode);

    // Give the image to OpenGL
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // 加载并生成纹理
    GLint const format = mapImageToGLReadType(_n_channels);

    glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    if (GL_NEAREST != filter_mode) { glGenerateMipmap(GL_TEXTURE_2D); }
    //unbind
    glBindTexture(GL_TEXTURE_2D, -1);
}

int      OGLTexture2D::getWidth() const { return _width; }
int      OGLTexture2D::getHeight() const { return _height; }
uint32_t OGLTexture2D::getTextureID() const { return _texture_id; }

void OGLTexture2D::bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);// 在绑定纹理之前先激活纹理单元
    glBindTexture(GL_TEXTURE_2D, _texture_id);
}

bool OGLTexture2D::operator==(const ITexture2D &other) const {
    return this->_texture_id == other.getTextureID();
}

}// namespace taixu