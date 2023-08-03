//
// Created by xmmmmmovo on 2023/4/27.
//

#include "image_helper.hpp"


namespace taixu {

std::unique_ptr<stbi_uc, FreeDeleter>
loadImage(std::filesystem::path const& path, int* width, int* height,
          int* channels, int desired_channels, bool flip_vertically) {
    stbi_set_flip_vertically_on_load(flip_vertically);
    return std::unique_ptr<stbi_uc, FreeDeleter>(
            stbi_load(path.generic_string().c_str(), width, height, channels,
                      desired_channels));
}

std::unique_ptr<stbi_uc, FreeDeleter> compressImage(stbi_uc* data, int width,
                                                    int height, int channels,
                                                    int* out_size) {
    std::unique_ptr<stbi_uc, FreeDeleter> compressed(
            new stbi_uc[width * height * channels]);

    return nullptr;
}

}// namespace taixu