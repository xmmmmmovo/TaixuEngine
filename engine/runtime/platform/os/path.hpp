//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_PATH_HPP
#define TAIXUENGINE_PATH_HPP

#include <filesystem>
#include <string>
#include <vector>

namespace taixu {

std::filesystem::path getRelativePath(const std::filesystem::path& directory,
                                      const std::filesystem::path& file_path);

std::vector<std::string> getPathSegments(
        const std::filesystem::path& file_path);

/**
 * @brief
 * @param file_path
 * @return
 */
std::vector<std::string> getFileExtensions(
        const std::filesystem::path& file_path);

/**
 * @brief get last extension
 *
 * like: shader.goo.foo.bar -> output: .bar
 *
 * @param file_path
 * @return
 */
std::string getLastExtension(const std::filesystem::path& file_path);

std::string getFilePureName(const std::string&);


}// namespace taixu

#endif//TAIXUENGINE_PATH_HPP