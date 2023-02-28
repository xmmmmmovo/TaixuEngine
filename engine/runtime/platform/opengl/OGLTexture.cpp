//
// Created by xmmmmmovo on 2023/2/23.
//

#include "OGLTexture.hpp"

#include "platform/os/path.hpp"

namespace taixu {

GLint mapImageToGLReadType(std::string const &ext) {
    if (".jpg" == ext) {
        return GL_RGB;
    } else if (".png" == ext) {
        return GL_RGBA;
    }
    return 0;
}

OGLTexture::OGLTexture(const std::string_view &path,
                       GLint                   filter_mode = GL_LINEAR,
                       GLint what_happens_at_edge          = GL_REPEAT) {
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, what_happens_at_edge);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, what_happens_at_edge);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_mode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_mode);

    // Give the image to OpenGL
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    stbi_set_flip_vertically_on_load(true);
    // 加载并生成纹理
    unsigned char *data =
            stbi_load(path.data(), &width, &height, &n_channels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, (4 == n_channels ? GL_RGBA : GL_RGB),
                     width, height, 0,
                     mapImageToGLReadType(getLastExtension(path)),
                     GL_UNSIGNED_BYTE, data);
        if (GL_NEAREST != filter_mode) { glGenerateMipmap(GL_TEXTURE_2D); }
    } else {
        spdlog::error("Failed to load texture");
    }

    stbi_image_free(data);
    //unbind
    glBindTexture(GL_TEXTURE_2D, -1);
}

int      OGLTexture::getWidth() const { return width; }
int      OGLTexture::getHeight() const { return height; }
uint32_t OGLTexture::getTextureID() const { return texture_id; }

void OGLTexture::bind(uint32_t slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);// 在绑定纹理之前先激活纹理单元
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

bool OGLTexture::operator==(const ITexture &other) const {
    return this->texture_id == other.getTextureID();
}

OGLTexture::~OGLTexture() { glDeleteTextures(1, &texture_id); }
}// namespace taixu