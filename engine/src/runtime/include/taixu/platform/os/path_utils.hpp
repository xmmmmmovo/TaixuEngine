/**
 * @file path_utils.hpp
 * @author xmmmmmovo
 * @brief
 * @version 0.1
 * @date 2024-9
 *
 * @copyright Copyright (c) 2024 xmmmmmovo
 *
 */

#pragma once

#include <filesystem>

namespace taixu {

std::filesystem::path getRelativePath(const std::filesystem::path& directory, const std::filesystem::path& file_path);

std::filesystem::path fromRelativePath(const std::filesystem::path& directory,
                                       const std::filesystem::path& relative_path);

std::filesystem::path fromRelativePath(const std::filesystem::path& relative_path);

/**
 * @brief 根据不同os获取磁盘根目录
 */
std::filesystem::path getRootPath();

/**
 * @brief get parent directory of file path.
 */
[[maybe_unused]] std::filesystem::path getDirectoryPath(const std::filesystem::path& file_path);

}// namespace taixu
