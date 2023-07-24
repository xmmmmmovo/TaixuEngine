//
// Created by xmmmmmovo on 2023/4/27.
//

#include "image_helper.hpp"

namespace taixu {

stbi_uc* loadImage(std::filesystem::path const& path, int* width, int* height,
                   int* channels, int desired_channels, bool flip_vertically) {
    stbi_set_flip_vertically_on_load(flip_vertically);
    return stbi_load(path.generic_string().c_str(), width, height, channels,
                     desired_channels);
}

}// namespace taixu