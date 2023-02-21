//
// Created by xmmmmmovo on 2023/2/18.
//

#ifndef TAIXUENGINE_FILE_SERVICE_HPP
#define TAIXUENGINE_FILE_SERVICE_HPP

#include <filesystem>
#include <vector>

namespace taixu {

std::vector<std::filesystem::path> getFiles(
        const std::filesystem::path& directory);

}

#endif//TAIXUENGINE_FILE_SERVICE_HPP
