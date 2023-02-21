//
// Created by xmmmmmovo on 2023/2/18.
//

#include "path.hpp"

namespace taixu {

std::filesystem::path getRelativePath(const std::filesystem::path& directory,
                                      const std::filesystem::path& file_path) {
    return file_path.lexically_relative(directory);
}

std::vector<std::string> getPathSegments(
        const std::filesystem::path& file_path) {
    std::vector<std::string> segments;
    for (auto iter = file_path.begin(); iter != file_path.end(); ++iter) {
        segments.emplace_back(iter->generic_string());
    }
    return segments;
}

std::tuple<std::string, std::string, std::string> getFileExtensions(
        const std::filesystem::path& file_path) {
    return std::make_tuple(
            file_path.extension().generic_string(),
            file_path.stem().extension().generic_string(),
            file_path.stem().stem().extension().generic_string());
}

std::string getFilePureName(const std::string& file_full_name) {
    std::string file_pure_name = file_full_name;
    auto        pos            = file_full_name.find_first_of('.');
    if (pos != std::string::npos) {
        file_pure_name = file_full_name.substr(0, pos);
    }

    return file_pure_name;
}

}// namespace taixu::platform
