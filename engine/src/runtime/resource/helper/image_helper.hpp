//
// Created by xmmmmmovo on 2023/4/27.
//

#ifndef ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP
#define ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP

#include <stb_dxt.h>
#include <stb_image.h>

#include <filesystem>

namespace taixu {

/**
 * @brief 加载图片
 */
stbi_uc* loadImage(std::filesystem::path const& path, int* width, int* height,
                   int* channels, int desired_channels = 0,
                   bool flip_vertically = true);

/**
 * @brief 压缩图片
 */
stbi_uc* compressImage(stbi_uc* data, int width, int height, int channels,
                       int* out_size, int desired_channels = 4);

}// namespace taixu

#endif// ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP
