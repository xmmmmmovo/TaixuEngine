//
// Created by xmmmmmovo on 2023/4/27.
//

#ifndef ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP
#define ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP

#include <filesystem>

#include "resource/converted_data/image.hpp"

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
std::shared_ptr<Image> loadImage(std::filesystem::path const& path, int desired_channels = 4,
                                 bool is_srgb = false, bool flip_vertically = true);

/**
 * @brief 压缩图片
 * @param image
 * @param width
 * @param height
 * @param channels
 * @return
 */
bool compressImage(std::shared_ptr<Image> const& image, int width, int height, int channels);

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
std::unique_ptr<uint8_t> combineImages(uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t* alpha,
                                       int width, int height);

}// namespace taixu

#endif// ENGINE_RUNTIME_RESOURCE_HELPER_IMAGE_HELPER_HPP
