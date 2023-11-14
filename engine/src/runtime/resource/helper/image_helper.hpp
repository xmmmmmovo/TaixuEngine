//
// Created by xmmmmmovo on 2023/4/27.
//

#ifndef ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP
#define ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP

#include <filesystem>

#include <common/utils/pointer_utils.hpp>

#include "runtime/resource/res_type/raw_data/texture.hpp"

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
std::optional<Image> loadImage(std::filesystem::path const& path,
                               int desired_channels = 4, bool is_srgb = false,
                               bool flip_vertically = true);

/**
 * @brief 压缩图片
 * @param data
 * @param width
 * @param height
 * @param channels
 * @param out_size
 * @return
 */
free_unique_ptr<uint8_t> compressImage(uint8_t* data, int width, int height,
                                       int channels, int* out_size);

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
free_unique_ptr<uint8_t> combineImages(uint8_t* red, uint8_t* green,
                                       uint8_t* blue, uint8_t* alpha, int width,
                                       int height);

}// namespace taixu

#endif// ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP
