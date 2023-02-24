//
// Created by xmmmmmovo on 2023/2/23.
//

#include "OGLTexture.hpp"

namespace taixu {

OGLTexture::OGLTexture(const std::string_view &path) {
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // TODO: debug for this texture
    stbi_set_flip_vertically_on_load(true);
    // 加载并生成纹理
    unsigned char *data =
            stbi_load(path.data(), &width, &height, &n_channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        spdlog::error("Failed to load texture");
    }
    stbi_image_free(data);
}

int      OGLTexture::getWidth() const { return width; }
int      OGLTexture::getHeight() const { return height; }
uint32_t OGLTexture::getTextureID() const { return texture_id; }

void OGLTexture::bind(uint32_t slot) const {}

bool OGLTexture::operator==(const ITexture &other) const {
    return this->texture_id == other.getTextureID();
}
}// namespace taixu