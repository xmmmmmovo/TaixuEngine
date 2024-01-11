//
// Created by xmmmmmovo on 2023/4/27.
//

#include "resource/helper/image_helper.hpp"

#include <common/utils/binary_utils.hpp>

#define STB_DXT_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include <common/exception/notimplemented_exception.hpp>

#include <stb_dxt.h>
#include <stb_image.h>
#include <stb_image_resize2.h>

namespace taixu {

std::optional<Image> loadImage(std::filesystem::path const& path,
                               int desired_channels, bool is_srgb,
                               bool flip_vertically) {
    stbi_set_flip_vertically_on_load(flip_vertically);

    int32_t width, height, channels;

    uint8_t* data = stbi_load(path.generic_string().c_str(), &width, &height,
                              &channels, desired_channels);
    if (nullptr == data) { return std::nullopt; }

    // resize to 2^n size;
    std::int32_t       offset   = bitScanReverse32(width);
    std::int32_t const offset_h = bitScanReverse32(height);

    if (offset == ZERO_VALUE_FLAG) {
        offset = offset_h;
    } else {
        offset = std::max(offset, offset_h);
    }

    // get new size of 2^n
    std::int32_t const new_size      = 1 << offset;
    std::int32_t const new_data_size = new_size * new_size * desired_channels;

    if (new_size != width || new_size != height) {
        // call stb resize
        uint8_t*       out_data = malloc_bytes<uint8_t>(new_data_size);
        const uint8_t* ret =
                stbir_resize_uint8_linear(data, width, height, 0, out_data,
                                          new_size, new_size, 0, STBIR_RGBA);
        // free origin data
        free(data);
        if (nullptr == ret) {
            free(out_data);
            return std::nullopt;
        }
        data = out_data;
    }

    return Image{
            .data             = data,
            .size             = new_data_size,
            .w                = new_size,
            .h                = new_size,
            .channels         = channels,
            .desired_channels = desired_channels,
            .is_srgb          = is_srgb,
    };
}

free_unique_ptr<uint8_t> compressImage(uint8_t* data, int width, int height,
                                       int channels, int* out_size) {
    return nullptr;
}

free_unique_ptr<uint8_t> combineImages(uint8_t* red, uint8_t* green,
                                       uint8_t* blue, uint8_t* alpha, int width,
                                       int height) {
    NOT_IMPL_ASSERT();
    return nullptr;
}

}// namespace taixu