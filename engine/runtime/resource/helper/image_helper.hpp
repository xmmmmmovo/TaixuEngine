//
// Created by xmmmmmovo on 2023/4/27.
//

#ifndef ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP
#define ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP

#include <stb_image.h>

namespace taixu {

/**
 * @brief 加载图片
 */
stbi_uc *loadImage(std::filesystem::path const &path, int *width, int *height,
                   int *channels, int desired_channels = 4,
                   bool flip_vertically = true);


}// namespace taixu

#endif//ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP
