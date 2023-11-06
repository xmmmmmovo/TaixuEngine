//
// Created by xmmmmmovo on 2023/4/27.
//

#include "image_helper.hpp"

#include <common/utils/binary_utils.hpp>

namespace taixu {

std::unique_ptr<stbi_uc, FreeDeleter>
loadImage(std::filesystem::path const& path, int* width, int* height,
          int* channels, int desired_channels, bool srgb,
          bool flip_vertically) {
    stbi_set_flip_vertically_on_load(flip_vertically);
    stbi_uc* data = stbi_load(path.generic_string().c_str(), width, height,
                              channels, desired_channels);
    if (nullptr == data) { return nullptr; }

    // resize to 2^n size;
    std::int32_t       offset   = bitScanReverse32(*width);
    std::int32_t const offset_h = bitScanReverse32(*height);

    if (offset == ZERO_VALUE_FLAG) {
        offset = offset_h;
    } else {
        offset = std::max(offset, offset_h);
    }

    // get new size of 2^n
    std::int32_t const new_size = 1 << offset;

    // call stb resize


    return std::unique_ptr<stbi_uc, FreeDeleter>();
}

std::unique_ptr<stbi_uc, FreeDeleter> compressImage(stbi_uc* data, int width,
                                                    int height, int channels,
                                                    int* out_size) {
    std::unique_ptr<stbi_uc, FreeDeleter> compressed(
            new stbi_uc[width * height * channels]);


    return nullptr;
}

}// namespace taixu