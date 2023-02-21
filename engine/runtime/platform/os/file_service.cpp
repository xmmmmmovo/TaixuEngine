//
// Created by xmmmmmovo on 2023/2/18.
//

#include "file_service.hpp"

namespace taixu::platform {
std::vector<std::filesystem::path> getFiles(
        const std::filesystem::path& directory) {
    std::vector<std::filesystem::path> files;
    auto                               recursive_iter =
            std::filesystem::recursive_directory_iterator{directory};
    std::copy_if(begin(recursive_iter), end(recursive_iter),
                 std::back_inserter(files),
                 [](std::filesystem::directory_entry const& directory_entry) {
                     return directory_entry.is_regular_file();
                 });
    return files;
}
}// namespace taixu::platform