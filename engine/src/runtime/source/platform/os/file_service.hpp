//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_FILE_SERVICE_HPP
#define TAIXUENGINE_FILE_SERVICE_HPP

#include <filesystem>
#include <fstream>
#include <vector>

namespace taixu {

std::vector<std::filesystem::path>
getFiles(const std::filesystem::path& directory);

bool removeFile(std::filesystem::path const& file_path);

bool removeDirectory(std::filesystem::path const& directory_path);

bool createDirectory(std::filesystem::path const& directory_path);

bool copyFile(std::filesystem::path const& source,
              std::filesystem::path const& destination);

bool copyDirectory(std::filesystem::path const& source,
                   std::filesystem::path const& destination);

bool moveFileOrDirectory(std::filesystem::path const& source,
                         std::filesystem::path const& destination);

std::ifstream openFile(std::filesystem::path const& file_path);

std::ofstream createFile(std::filesystem::path const& file_path);

}// namespace taixu

#endif// TAIXUENGINE_FILE_SERVICE_HPP
