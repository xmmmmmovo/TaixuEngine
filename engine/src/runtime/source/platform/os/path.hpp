//
// Created by xmmmmmovo on 2023/2/18.
//

#pragma once

#include <filesystem>

#include "common/hal/tx_string.hpp"

namespace taixu {

/*
 * @brief get path segments
 * @param file_path
 * @return
 */
std::vector<tx_string> getPathSegments(const std::filesystem::path& file_path);

/**
 * @brief
 * @param file_path
 * @return
 */
std::vector<tx_string> getFileExtensions(const std::filesystem::path& file_path);

/**
 * @brief get last extension
 *
 * like: shader.goo.foo.bar -> output: .bar
 *
 * @param file_path
 * @return
 */
tx_string getLastExtension(const std::filesystem::path& file_path);

tx_string getFilePureName(const tx_string& file_path);

}// namespace taixu
