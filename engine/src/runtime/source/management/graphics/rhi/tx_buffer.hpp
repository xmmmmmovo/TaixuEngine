//
// Created by xmmmmmovo on 2/1/2024.
//

#pragma once

namespace taixu {

enum class EnumTXBufferUsage : uint16_t {
    VERTEX_SHADER   = 1 << 0,
    FRAGMENT_SHADER = 1 << 1,
    UNIFORM_TEXTEL  = 1 << 2,
    VERTEX_BUFFER   = 1 << 3,
    INDICIES_BUFFER = 1 << 4
};

enum class EnumTXBufferSharingMode : uint8_t {
    // 独享
    EXCLUSIVE  = 0,
    // 共享
    CONCURRENT = 1
};

struct TXBufferCreateInfo {
    uint64_t                size{0};
    EnumTXBufferUsage       usage{};
    EnumTXBufferSharingMode sharing_mode{};
};

class TXBuffer : std::enable_shared_from_this<TXBuffer> {
public:
    virtual ~    TXBuffer()       = default;
    virtual void map()            = 0;
    virtual void updateResource() = 0;
    virtual void unmap()          = 0;
};

}// namespace taixu