//
// Created by xmmmmmovo on 2023/2/14.
//

#ifndef TAIXUENGINE_TEXTURE_HPP
#define TAIXUENGINE_TEXTURE_HPP
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <stb_image.h>

#include <cstdint>

#include "core/base/noncopyable.hpp"

namespace taixu {

class ITexture : private noncopyable {
public:
    virtual int      getWidth() const     = 0;
    virtual int      getHeight() const    = 0;
    virtual uint32_t getTextureID() const = 0;

    virtual void bind(uint32_t slot = 0) const = 0;

    virtual bool operator==(const ITexture& other) const = 0;
};

}// namespace taixu

#endif//TAIXUENGINE_TEXTURE_HPP
