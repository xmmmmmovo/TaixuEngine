//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_PATH_HPP
#define TAIXUENGINE_PATH_HPP

#include <filesystem>
#include <string>
#include <vector>

namespace taixu {

inline std::filesystem::path getRelativePath(
        const std::filesystem::path& directory,
        const std::filesystem::path& file_path);

inline std::filesystem::path fromRelativePath(
        const std::filesystem::path& directory,
        const std::filesystem::path& relative_path);

inline std::filesystem::path fromRelativePath(
        const std::filesystem::path& relative_path);

inline std::vector<std::string> getPathSegments(
        const std::filesystem::path& file_path);

/**
 * @brief
 * @param file_path
 * @return
 */
inline std::vector<std::string> getFileExtensions(
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

std::filesystem::path getRootPath();

/**
 * @brief 获取文件的文件夹路径
 */
[[maybe_unused]] std::filesystem::path getDirectoryPath(
        const std::filesystem::path& file_path);
}// namespace taixu

#endif//TAIXUENGINE_PATH_HPP
