//
// Created by xmmmmmovo on 2023/2/18.
//

#include <taixu/platform/os/path_utils.hpp>

#include "platform/os/path.hpp"

namespace taixu {

std::filesystem::path getRelativePath(const std::filesystem::path& directory, const std::filesystem::path& file_path) {
    return file_path.lexically_relative(directory);
}

// TODO: 检测这种实现方式是否可以

std::vector<tx_string> getPathSegments(const std::filesystem::path& file_path) {
    std::vector<tx_string> segments;
    for (auto iter = file_path.begin(); iter != file_path.end(); ++iter) {
        segments.emplace_back(iter->generic_string().data());
    }
    return segments;
}

std::vector<tx_string> getFileExtensions(const std::filesystem::path& file_path) {
    std::vector<tx_string> res(1);
    for (auto p = file_path; !p.extension().empty(); p = p.stem()) {
        res.emplace_back(p.extension().generic_string().data());
    }
    return res;
}

tx_string getLastExtension(const std::filesystem::path& file_path) {
    return file_path.extension().generic_string().data();
}

tx_string getFilePureName(const tx_string& file_full_name) {
    tx_string file_pure_name = file_full_name;
    auto      pos            = file_full_name.find_first_of('.');
    if (pos != std::string::npos) {
        file_pure_name = file_full_name.substr(0, pos);
    }

    return file_pure_name;
}

std::filesystem::path fromRelativePath(const std::filesystem::path& directory, const std::filesystem::path& file_path) {
    return directory / file_path;
}

std::filesystem::path fromRelativePath(const std::filesystem::path& relative_path) {
    return std::filesystem::current_path() / relative_path;
}

std::filesystem::path getRootPath() {
    return std::filesystem::current_path().root_path();
}

std::filesystem::path getDirectoryPath(const std::filesystem::path& file_path) {
    return file_path.parent_path();
}

}// namespace taixu
