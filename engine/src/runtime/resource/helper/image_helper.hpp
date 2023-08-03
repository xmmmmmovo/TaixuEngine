//
// Created by xmmmmmovo on 2023/4/27.
//

#ifndef ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP
#define ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP

#include <stb_dxt.h>
#include <stb_image.h>

#include <filesystem>

#include <common/utils/pointer_utils.hpp>

namespace taixu {

/**
 * @brief 加载图片
 * @param path
 * @param width
 * @param height
 * @param channels
 * @param desired_channels
 * @param flip_vertically
 * @return
 */
std::unique_ptr<stbi_uc, FreeDeleter>
loadImage(std::filesystem::path const& path, int* width, int* height,
          int* channels, int desired_channels = 4, bool flip_vertically = true);

/**
 * @brief 压缩图片
 * @param data
 * @param width
 * @param height
 * @param channels
 * @param out_size
 * @return
 */
std::unique_ptr<stbi_uc, FreeDeleter> compressImage(stbi_uc* data, int width,
                                                    int height, int channels,
                                                    int* out_size);

/**
 * @brief 合并多个单通道图片
 * @param red
 * @param green
 * @param blue
 * @param alpha
 * @param width
 * @param height
 * @return
 */
std::unique_ptr<stbi_uc, FreeDeleter>
combineImages(stbi_uc* red, stbi_uc* green,
              stbi_uc* blue, stbi_uc* alpha,
              int width, int height);

}// namespace taixu

#endif// ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP
