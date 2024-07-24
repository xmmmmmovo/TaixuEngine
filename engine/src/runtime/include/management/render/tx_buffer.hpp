//
// Created by xmmmmmovo on 2/1/2024.
//

#pragma once

#include "common/designs/noncopyable.hpp"

namespace taixu {

enum class TXBufferUsage : uint8_t {
    UNIFORM_TEXTEL  = 1 << 0,
    VERTEX_BUFFER   = 1 << 1,
    INDICIES_BUFFER = 1 << 2,
    CONSTANT_BUFFER = 1 << 3
};

enum class TXBufferSharingMode : uint8_t {
    // 独享
    EXCLUSIVE  = 0,
    // 共享
    CONCURRENT = 1
};

enum class TXBufferMemoryUsage : uint8_t {
    GPU_READ_WRITE,
    GPU_READ_ONLY,
    CPU_WRITE_GPU_READ,
    CPU_GPU_READ_WRITE
};


struct TXBufferCreateInfo {
    uint64_t            size{0};
    const void*         data_ptr{nullptr};
    TXBufferUsage       usage{};
    TXBufferMemoryUsage memory_usage{};
    TXBufferSharingMode sharing_mode{};
    size_t              stride{0};
};

class TXBuffer : public std::enable_shared_from_this<TXBuffer>, public Noncopyable {
public:
    ~TXBuffer() override = default;
};

}// namespace taixu
