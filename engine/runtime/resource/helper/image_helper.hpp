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
stbi_uc *load_image(std::filesystem::path const &path, int *width, int *height,
                    int *channels, int desired_channels = 4);


}// namespace taixu

#endif//ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP