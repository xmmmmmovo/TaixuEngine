//
// Created by xmmmmmovo on 2023/4/27.
//

#include "image_helper.hpp"

#include <common/utils/binary_utils.hpp>

#define STB_DXT_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include <stb_dxt.h>
#include <stb_image.h>
#include <stb_image_resize2.h>

#include <mimalloc-override.h>

#include "common/log/logger.hpp"

static constexpr std::int32_t ZERO_VALUE_FLAG   = -1;
static constexpr auto         STB_IMAGE_DELETER = [](void* img) { stbi_image_free(img); };

namespace taixu {

std::shared_ptr<Image> loadImage(std::filesystem::path const& path, const int desired_channels,
                                 const bool is_srgb, const bool flip_vertically) {
    stbi_set_flip_vertically_on_load(flip_vertically);

    int32_t width{0}, height{0}, channels{0};

    uint8_t* data =
            stbi_load(path.generic_string().c_str(), &width, &height, &channels, desired_channels);
    if (nullptr == data || width < 0 || height < 0) {
        ERROR_LOG("Read Image data failed!");
        return nullptr;
    }

    std::shared_ptr<Image> image = std::make_shared<Image>();
    image->channels              = channels;
    image->desired_channels      = desired_channels;
    image->is_srgb               = is_srgb;

    if (width == height && isPowerOfTwo(static_cast<uint32_t>(width)) &&
        isPowerOfTwo(static_cast<uint32_t>(height))) {
        image->data = std::shared_ptr<uint8_t[]>(data, STB_IMAGE_DELETER);// NOLINT
        image->size = width * height;
        image->w    = width;
        image->h    = height;
        return image;
    }

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
        auto*          out_data = static_cast<uint8_t*>(malloc(new_data_size));
        const uint8_t* ret = stbir_resize_uint8_linear(data, width, height, 0, out_data, new_size,
                                                       new_size, 0, STBIR_RGBA);
        // free origin data
        free(data);
        if (nullptr == ret) {
            free(out_data);
            return nullptr;
        }
        data = out_data;
    }

    image->data = std::shared_ptr<uint8_t[]>(data, STB_IMAGE_DELETER);// NOLINT
    image->size = new_data_size;
    image->w    = new_size;
    image->h    = new_size;

    return image;
}

}// namespace taixu
