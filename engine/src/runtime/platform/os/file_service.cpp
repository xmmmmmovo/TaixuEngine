//
// Created by xmmmmmovo on 2023/2/18.
//

#include "file_service.hpp"

namespace taixu {

std::vector<std::filesystem::path>
getFiles(const std::filesystem::path& directory) {
    std::vector<std::filesystem::path> files;
    auto                               recursive_iter =
            std::filesystem::recursive_directory_iterator{directory};
    // TODO: this may cause mem explosion, Need to be optimized!
    std::copy_if(begin(recursive_iter), end(recursive_iter),
                 std::back_inserter(files),
                 [](std::filesystem::directory_entry const& directory_entry) {
                     return directory_entry.is_regular_file();
                 });
    return files;
}

bool removeFile(std::filesystem::path const& file_path) {
    return std::filesystem::remove(file_path);
}

bool removeDirectory(std::filesystem::path const& directory_path) {
    return std::filesystem::remove_all(directory_path);
}

bool createDirectory(std::filesystem::path const& directory_path) {
    return std::filesystem::create_directories(directory_path);
}

bool copyFile(std::filesystem::path const& source,
              std::filesystem::path const& destination) {
    return std::filesystem::copy_file(source, destination);
}

bool copyDirectory(std::filesystem::path const& source,
                   std::filesystem::path const& destination) {
    std::error_code ec;
    std::filesystem::copy(source, destination, ec);
    return !static_cast<bool>(ec);
}

bool moveFileOrDirectory(std::filesystem::path const& source,
                         std::filesystem::path const& destination) {
    std::error_code ec;
    std::filesystem::rename(source, destination, ec);
    return !static_cast<bool>(ec);
}

std::ifstream openFile(std::filesystem::path const& file_path) {
    std::ifstream ifstream{file_path};
    if (!ifstream.is_open()) {
        throw std::runtime_error("Failed to open file: {}" +
                                 file_path.string());
    }
    return ifstream;
}

std::ofstream createFile(std::filesystem::path const& file_path) {
    std::ofstream ofstream{file_path};
    if (!ofstream.is_open()) {
        throw std::runtime_error("Failed to create file: {}" +
                                 file_path.string());
    }
    return ofstream;
}

}// namespace taixu