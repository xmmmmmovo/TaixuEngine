//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_PATH_HPP
#define TAIXUENGINE_PATH_HPP

#include <filesystem>
#include <string>
#include <vector>

namespace taixu::platform {

std::filesystem::path getRelativePath(const std::filesystem::path& directory,
                                      const std::filesystem::path& file_path);

std::vector<std::string> getPathSegments(
        const std::filesystem::path& file_path);

std::tuple<std::string, std::string, std::string> getFileExtensions(
        const std::filesystem::path& file_path);

std::string getFilePureName(const std::string&);


}// namespace taixu::platform

#endif//TAIXUENGINE_PATH_HPP
