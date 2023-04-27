//
// Created by xmmmmmovo on 2023/4/27.
//

#include "image_helper.hpp"

namespace taixu {

stbi_uc *load_image(std::filesystem::path const &path, int *width, int *height,
                    int *channels, int desired_channels) {
    return stbi_load(path.string().c_str(), width, height, channels,
                     desired_channels);
}

}// namespace taixu